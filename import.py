#!/usr/bin/env python

import os, sys, re, shutil, codecs
open = codecs.open
from os.path import abspath, exists, join, isfile

assert abspath(sys.argv[0]) == join(abspath(os.getcwd()), "import.py")
OUTPUT = join(abspath(os.getcwd()), "subnacl")
os.mkdir(OUTPUT)
INCLUDE = join(OUTPUT, "include")
os.mkdir(INCLUDE)
NACL = sys.argv[1]

def lines(*path):
    return [line.strip() for line in open(join(NACL, *path),"r")]

MACROS = lines("MACROS")

for op in lines("OPERATIONS"):
    assert op.startswith("crypto_")
    opname = op[len("crypto_"):]
    op_dir = join(NACL, op)
    #op_macros = [m[len(op+"_"):] for m in MACROS if m.startswith(op)]
    op_macros = [m for m in MACROS if m == op or m.startswith("%s_" % op)]

    # each operation includes several primitives. Sometimes you care about
    # using a specific primitive, sometimes you just want to use the default
    for prim in os.listdir(op_dir):
        prim_dir = join(op_dir, prim)
        if not exists(join(prim_dir, "used")):
            continue # nacl might not mark everything as used
        # 'selected' means this is a default. E.g. the presence of
        # crypto_hash/sha512/selected means that the generic crypto_hash()
        # should invoke crypto_hash_sha512(), and that crypto_hash_BYTES is
        # #defined to crypto_hash_sha512_BYTES.
        selected = exists(join(prim_dir, "selected"))

        # now which implementations are available? nacl files these by
        # looking for "api.h" files. We cheat and assume they're all in
        # immediate subdirectories (nacl/do can find them in arbitrarily-deep
        # subdirectories)
        implementations = []
        for impl in os.listdir(prim_dir):
            if not exists(join(prim_dir, impl, "api.h")):
                continue
            implementations.append(impl)
        # which implementation should we use? Prefer the 'ref' or 'portable'
        # ones for now.
        if "ref" in implementations:
            preferred = "ref"
        elif "portable" in implementations:
            preferred = "portable"
        else:
            print("unable to find acceptable impl of %s/%s in %s" %
                  (op, prim, ",".join(implementations)))
            continue
        print("%s %s %s" % (op, prim, preferred))

        outdir = join(OUTPUT, "%s_%s" % (opname, prim))
        os.mkdir(outdir)

        impldir = join(prim_dir, preferred)
        for fn in os.listdir(impldir):
            absfn = join(impldir, fn)
            assert isfile(absfn), "cannot handle subdirs: %s/%s" % (impldir, fn)
            if fn.endswith(".c"):
                # need to modify it
                out = open(join(outdir, fn), "w", encoding="utf-8")
                for line in open(absfn, "r", encoding="utf-8").readlines():
                    if line.strip().startswith("#include"):
                        old = "%s.h" % op
                        if old in line:
                            new = "%s_%s.h" % (op, prim)
                            line = line.replace(old, new)
                    else:
                        for m in op_macros:
                            # when processing crypto_hash, replace
                            # crypto_hash() with crypto_hash_sha256() and
                            # crypto_hash_BYTES with
                            # crypto_hash_sha256_BYTES, but leave
                            # crypto_hashblocks_OTHER alone
                            new = m.replace(op, "%s_%s" % (op, prim))
                            line = re.sub(r'\b%s\b' % m, new, line)
                    out.write(line)
                out.close()
            else:
                # don't try to modify it
                shutil.copy(absfn, outdir)

        out = open(join(INCLUDE, "%s_%s.h" % (op,prim)), "w")
        out.write("#ifndef %s_%s_H\n" % (op, prim))
        out.write("#define %s_%s_H\n" % (op, prim))
        out.write("\n")
        for line in open(join(impldir, "api.h"), "r").readlines():
            line = line.replace("CRYPTO_", "%s_%s_" % (op, prim))
            out.write(line)
        out.write("\n")
        out.write("#ifdef __cplusplus\n")
        out.write("\n")
        for line in open(join(NACL, "PROTOTYPES.cpp"), "r").readlines():
            if ("%s(" % op) in line or ("%s_" % op) in line:
                line = line.replace(op, "%s_%s" % (op, prim))
                out.write(line)
        out.write("\n")

        out.write('extern "C" {\n')
        out.write("#endif\n")
        out.write("\n")
        for line in open(join(NACL, "PROTOTYPES.c"), "r").readlines():
            if ("%s(" % op) in line or ("%s_" % op) in line:
                line = line.replace(op, "%s_%s" % (op, prim))
                out.write(line)
        out.write("\n")
        out.write("#ifdef __cplusplus\n")
        out.write("}\n")
        out.write("#endif\n")
        out.write("\n")
        out.write('#define %s_%s_IMPLEMENTATION "%s/%s/%s"\n'
                  % (op, prim, op, prim, preferred))
        out.write('#define %s_%s_VERSION "-"\n' % (op, prim))
        out.write("\n")
        out.write("#endif\n")
        out.close()

        # if this primitive is selected as a default, create a generic header
        # file for the operation
        if selected:
            out = open(join(INCLUDE, "%s.h" % op), "w")
            out.write("#ifndef %s_H\n" % op)
            out.write("#define %s_H\n" % op)
            out.write("\n")
            # this is the "selected" default
            out.write('#include "%s_%s.h"\n' % (op, prim))
            out.write("\n")
            for m in op_macros:
                m_prim = m.replace(op, "%s_%s" % (op,prim))
                out.write('#define %s %s\n' % (m, m_prim))
            out.write('#define %s_PRIMITIVE "%s"\n' % (op, prim))
            out.write('#define %s_IMPLEMENTATION %s_%s_IMPLEMENTATION\n'
                      % (op, op, prim))
            out.write('#define %s_VERSION %s_%s_VERSION\n' % (op, op, prim))
            out.write("\n")
            out.write("#endif\n")
            out.close()

            # and copy any C++ wrappers provided for this operation, which
            # will use the primitive referenced by that header file
            for fn in os.listdir(op_dir):
                print "C++ check", op_dir, fn
                if fn.startswith("wrapper-") and fn.endswith(".cpp"):
                    out = open(join(outdir, fn), "wb")
                    out.write(open(join(op_dir, fn), "rb").read())
                    out.close()

# create a few more include files
out = open(join(INCLUDE, "randombytes.h"), "w")
out.write("#ifndef randombytes_H\n")
out.write("#define randombytes_H\n")
out.write("\n")
out.write("extern void randombytes(unsigned char *,unsigned long long);\n")
out.write("#endif\n")
out.close()

out = open(join(INCLUDE, "crypto_uint32.h"), "w")
out.write("#ifndef crypto_uint32_H\n")
out.write("#define crypto_uint32_H\n")
out.write("\n")
out.write("typedef unsigned int crypto_uint32;\n")
out.write("#endif\n")
out.close()

out = open(join(INCLUDE, "crypto_uint64.h"), "w")
out.write("#ifndef crypto_uint64_H\n")
out.write("#define crypto_uint64_H\n")
out.write("\n")
out.write("typedef unsigned int crypto_uint64;\n")
out.write("#endif\n")
out.close()

os.mkdir(join(OUTPUT, "randombytes"))
shutil.copy(join(NACL, "randombytes", "devurandom.c"),
            join(OUTPUT, "randombytes", "devurandom.c"))
