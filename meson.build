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

robot = meson.source_root() / 'test' / 'robot'
robot_dump_names = robot / 'dump-names'
suggest_names = meson.source_root() / 'suggest_names'

test('robot', find_program('python3'),
        args: [
                '-m',
                'robot',
                '--pythonpath',
                robot_dump_names,
                '--pythonpath',
                suggest_names,
                '-vdump_names:' + dump_names.full_path(),
                robot],
        depends: dump_names)

tex_vcs_tag = vcs_tag(
        command: ['git', 'rev-parse', '--short', 'HEAD'],
        input: 'tex/version.tex.in',
        output: 'version.tex')

tex_test_list_output = 'test_list.tex'
tex_test_list = custom_target('Test List',
        command: [
                find_program('python3'),
                '-m',
                'robot',
                '--pythonpath',
                robot_dump_names,
                '--pythonpath',
                suggest_names,
                '-vdump_names:' + dump_names.full_path(),
                '--output=NONE',
                '--report=NONE',
                '--log=NONE',
                '--console=quiet',
                '--dryrun',
                '--prerunmodifier', 'Lister:' + tex_test_list_output,
                robot
        ],
        output: tex_test_list_output,
        depend_files: [
            files([
            'schema/varnames.json',
            'test/robot/dump-names/Lister.py',
            'test/robot/dump-names/__init__.robot',
            'test/robot/dump-names/Lister.py',
            'test/robot/dump-names/variables.robot',
            'test/robot/dump-names/libraries/Variables.py',
            'test/robot/suggest-names/__init__.robot',
            'test/robot/suggest-names/merge.robot',
            'test/robot/suggest-names/suggest.robot',
            'test/robot/suggest-names/resources/DatabaseKeywords.robot',
            'test/robot/suggest-names/libraries/DatabaseLibrary.py'])])

apt_packages = custom_target('Apt Package List',
        command: [
                find_program('yq'),
                '--raw-output',
                '.addons.apt.packages | .[]',
                '@INPUT@'
        ],
        capture: true,
        input: '.travis.yml',
        output: 'apt_packages.txt')

vim_doc = configure_file(input: 'vim/doc/suggest-names.txt',
        output: 'vim-doc.txt',
        copy: true)
schema = configure_file(input: 'schema/varnames.json',
        output: 'varnames.json',
        copy: true)

thesis = custom_target('Thesis pdf',
        command: [
                find_program('rubber'),
                '--pdf',
                '-I' + meson.source_root() / 'tex',
                '-I' + meson.source_root() / 'img',
                '-I' + meson.source_root() / 'vim' / 'doc',
                '-I' + meson.current_build_dir(),
                '--command', 'bibtex.path ' + meson.source_root() / 'tex',
                '@INPUT@'],
        build_by_default: true,
        input: 'thesis.tex',
        output: 'thesis.pdf',
        depends: [
            tex_vcs_tag,
            tex_test_list,
            apt_packages],
        depend_files: [
            vim_doc,
            schema,
            files([
                'img/elte_logo.eps',
                'tex/titlepage.tex',
                'tex/introduction.tex',
                'tex/user_documentation.tex',
                'tex/developer_documentation.tex',
                'tex/testing.tex',
                'tex/bibliography.bib',
                'tex/appendix.tex'])])
