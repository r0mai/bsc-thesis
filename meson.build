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
        'src/VariableDeclaration.cpp',
        include_directories: include_directory,
        cpp_args: [
            '-fno-exceptions', '-fno-rtti',
            '-Wno-comment'],
        dependencies: [boost_dependency, llvm_dependency])

robot_dump_names = meson.source_root() / 'test' / 'robot' / 'dump-names'

test('robot', find_program('robot'),
        args: [
                '-P',
                robot_dump_names,
                '-vdump_names:' + dump_names.full_path(),
                robot_dump_names],
        depends: dump_names)

tex_vcs_tag = vcs_tag(
        command: ['git', 'rev-parse', '--short', 'HEAD'],
        input: 'tex/version.tex.in',
        output: 'version.tex')

tex_test_list_output = 'test_list.tex'
tex_test_list = custom_target('Test List',
        command: [
                find_program('robot'),
                '-P',
                robot_dump_names,
                '-vdump_names:' + dump_names.full_path(),
                '--output=NONE',
                '--report=NONE',
                '--log=NONE',
                '--console=quiet',
                '--dryrun',
                '--prerunmodifier', 'Lister:' + tex_test_list_output,
                robot_dump_names
        ],
        output: tex_test_list_output,
        depend_files: [
            files([
            'test/robot/dump-names/Lister.py',
            'test/robot/dump-names/__init__.robot',
            'test/robot/dump-names/Lister.py',
            'test/robot/dump-names/variables.robot'])])

thesis = custom_target('Thesis pdf',
        command: [
                find_program('rubber'),
                '--pdf',
                '-I' + meson.source_root() / 'tex',
                '-I' + meson.source_root() / 'img',
                '-I' + meson.current_build_dir(),
                '@INPUT@'],
        build_by_default: true,
        input: 'thesis.tex',
        output: 'thesis.pdf',
        depends: [
            tex_vcs_tag,
            tex_test_list],
        depend_files: [
            files([
                'img/elte_logo.eps',
                'tex/titlepage.tex',
                'tex/introduction.tex',
                'tex/developer_documentation.tex'])])
