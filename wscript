import Options

subdirs = 'src'

def options(opt):
  opt.load('compiler_cxx')

def configure(conf):
  conf.env.CXXFLAGS += ['-O2', '-Wall', '-g', '-pipe']

  conf.load('compiler_cxx')
  # conf.check_cfg(package = 'pficommon', args = '--cflags --libs')
  # for mac
  conf.check_cxx(lib = ['pficommon_text'],
                 uselib_store = 'PFICOMMON')


def build(bld):
  bld.recurse(subdirs)

