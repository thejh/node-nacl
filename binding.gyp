# -*- python -*-
# (actually .gyp is JSON, but allows #-comments and trailing commas)

{
    "targets": [
        {
            "target_name": "nacl",
            "include_dirs": ["subnacl/include"],
            # re-enable C++ exceptions (the "!" is the important bit)
            # https://github.com/TooTallNate/node-gyp/issues/17
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "conditions": [
                ['OS=="mac"', {
                    "xcode_settings": {
                        "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
                        }}]],
            "sources": [
                "node_nacl.cc",

                # created with
                #  python import.py
                #  find subnacl -type f -name '*.c' -or -name '*.cpp'|perl -ne 's/\s+$//; print "                \"$_\",\n";'
                "subnacl/auth_hmacsha256/hmac.c",
                "subnacl/auth_hmacsha256/verify.c",
                "subnacl/auth_hmacsha512256/hmac.c",
                "subnacl/auth_hmacsha512256/verify.c",
                "subnacl/auth_hmacsha512256/wrapper-auth.cpp",
                "subnacl/auth_hmacsha512256/wrapper-verify.cpp",
                "subnacl/box_curve25519xsalsa20poly1305/after.c",
                "subnacl/box_curve25519xsalsa20poly1305/before.c",
                "subnacl/box_curve25519xsalsa20poly1305/box.c",
                "subnacl/box_curve25519xsalsa20poly1305/keypair.c",
                "subnacl/box_curve25519xsalsa20poly1305/wrapper-box.cpp",
                "subnacl/box_curve25519xsalsa20poly1305/wrapper-keypair.cpp",
                "subnacl/box_curve25519xsalsa20poly1305/wrapper-open.cpp",
                "subnacl/core_hsalsa20/core.c",
                "subnacl/core_salsa20/core.c",
                "subnacl/core_salsa2012/core.c",
                "subnacl/core_salsa208/core.c",
                "subnacl/hash_sha256/hash.c",
                "subnacl/hash_sha512/hash.c",
                "subnacl/hash_sha512/wrapper-hash.cpp",
                "subnacl/hashblocks_sha256/blocks.c",
                "subnacl/hashblocks_sha512/blocks.c",
                "subnacl/hashblocks_sha512/wrapper-empty.cpp",
                "subnacl/onetimeauth_poly1305/auth.c",
                "subnacl/onetimeauth_poly1305/verify.c",
                "subnacl/onetimeauth_poly1305/wrapper-auth.cpp",
                "subnacl/onetimeauth_poly1305/wrapper-verify.cpp",
                "subnacl/randombytes/devurandom.c",
                "subnacl/scalarmult_curve25519/base.c",
                "subnacl/scalarmult_curve25519/smult.c",
                "subnacl/secretbox_xsalsa20poly1305/box.c",
                "subnacl/secretbox_xsalsa20poly1305/wrapper-box.cpp",
                "subnacl/secretbox_xsalsa20poly1305/wrapper-open.cpp",
                "subnacl/sign_edwards25519sha512batch/fe25519.c",
                "subnacl/sign_edwards25519sha512batch/ge25519.c",
                "subnacl/sign_edwards25519sha512batch/sc25519.c",
                "subnacl/sign_edwards25519sha512batch/sign.c",
                "subnacl/sign_edwards25519sha512batch/wrapper-keypair.cpp",
                "subnacl/sign_edwards25519sha512batch/wrapper-sign-open.cpp",
                "subnacl/sign_edwards25519sha512batch/wrapper-sign.cpp",
                "subnacl/stream_aes128ctr/afternm.c",
                "subnacl/stream_aes128ctr/beforenm.c",
                "subnacl/stream_aes128ctr/common.c",
                "subnacl/stream_aes128ctr/consts.c",
                "subnacl/stream_aes128ctr/int128.c",
                "subnacl/stream_aes128ctr/stream.c",
                "subnacl/stream_aes128ctr/xor_afternm.c",
                "subnacl/stream_salsa20/stream.c",
                "subnacl/stream_salsa20/xor.c",
                "subnacl/stream_salsa2012/stream.c",
                "subnacl/stream_salsa2012/xor.c",
                "subnacl/stream_salsa208/stream.c",
                "subnacl/stream_salsa208/xor.c",
                "subnacl/stream_xsalsa20/stream.c",
                "subnacl/stream_xsalsa20/wrapper-stream.cpp",
                "subnacl/stream_xsalsa20/wrapper-xor.cpp",
                "subnacl/stream_xsalsa20/xor.c",
                "subnacl/verify_16/verify.c",
                "subnacl/verify_32/verify.c",
                ],
        }
    ]
}
