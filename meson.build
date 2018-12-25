project('dump-names', 'cpp', default_options: ['cpp_std=c++14'])

llvm_dependency = dependency('llvm')
boost_dependency = dependency('boost')

dump_names = shared_module('dump_names',
		'src/plugin.cpp',
		dependencies: [boost_dependency, llvm_dependency])
