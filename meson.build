project('asciidisplay', 'c',
        meson_version: '>=1.3.0',
        default_options: ['c_std=c17'])

asciidisplay_src = []
asciidisplay_includes = []

subdir('src')

asciidisplay = executable('asciidisplay', asciidisplay_src,
                          include_directories: asciidisplay_includes)

prog_objcopy = find_program('objcopy')
input_bfdname = meson.get_external_property('input_bfdname')
custom_target('asciidisplay_srecord',
	      build_by_default: true,
	      output: 'asciidisplay.s19',
	      input: asciidisplay,
	      command : [prog_objcopy, '-I'+input_bfdname,
			         '@INPUT@', '-Osrec', '@OUTPUT@'])
