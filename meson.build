project('dump-names', 'cpp',
		default_options: ['cpp_std=c++14'])

llvm_dependency = dependency('llvm')
boost_dependency = dependency('boost')

include_directory = include_directories('include')

dump_names = shared_module('dump_names',
		'src/plugin.cpp',
		'src/AstAction.cpp',
		'src/AstConsumer.cpp',
		'src/AstVisitor.cpp',
		include_directories: include_directory,
		cpp_args: [
			'-fno-exceptions', '-fno-rtti',
			'-Wno-comment'],
		dependencies: [boost_dependency, llvm_dependency])

tex_vcs_tag = vcs_tag(
		command: ['git', 'rev-parse', '--short', 'HEAD'],
		input: 'tex/version.tex.in',
		output: 'version.tex')

thesis = custom_target('Thesis pdf',
		command: [
				find_program('rubber'),
				'--pdf',
				'-I' + meson.source_root() / 'tex',
				'-I' + meson.source_root() / 'img',
				'@INPUT@'],
		build_by_default: true,
		input: 'thesis.tex',
		output: 'thesis.pdf',
		depends: tex_vcs_tag,
		depend_files: [
			files([
				'img/elte_logo.eps',
				'tex/titlepage.tex',
				'tex/introduction.tex'])])
