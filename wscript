srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

def pre(bld):
  import Utils
  Utils.exec_command(bld.path.abspath()+'/do')

def build(bld):
  #bld.add_pre_fun(pre)
  bld.env.LIBPATH_NACL=[bld.path.abspath()+'/build/localhost/lib/x86/']
  bld.env.STATICLIB_NACL="nacl"
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.cxxflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-DEV_MULTIPLICITY=0"]
  obj.target = "node_nacl"
  obj.source = "node_nacl.cc"
  obj.includes = bld.path.abspath()+'/build/localhost/include/x86/'
  obj.uselib = 'NACL'
  obj.add_obj_file("cpucycles.o")
  obj.add_obj_file("randombytes.o")
