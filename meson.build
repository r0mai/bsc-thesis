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
examples = meson.source_root() / 'examples'

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

llvm_ppa = custom_target('LLVM PPA',
        command: [
                find_program('yq'),
                '--raw-output',
                '.addons.apt.sources[0].sourceline',
                '@INPUT@'
        ],
        capture: true,
        input: '.travis.yml',
        output: 'llvm_ppa.txt')

vim_doc = configure_file(input: 'vim/doc/suggest-names.txt',
        output: 'vim-doc.txt',
        copy: true)
schema = configure_file(input: 'schema/varnames.json',
        output: 'varnames.json',
        copy: true)
example_cpp = configure_file(input: examples / 'example.cpp',
        output: 'example.cpp',
        copy: true)
databasekeywords = configure_file(
        input: 'test/robot/suggest-names/resources/DatabaseKeywords.robot',
        output: 'DatabaseKeywords.robot',
        copy: true)
gettraceback = meson.source_root() / 'gettraceback.sh'

suggest_names_help = custom_target('suggest_names --help',
        command: [
                find_program('env'),
                'COLUMNS=60',
                'python3',
                suggest_names / 'suggest_names',
                '--help'],
        capture: true,
        depend_files: [
                suggest_names / 'suggest_names',
                suggest_names / 'database.py',
                suggest_names / 'merge.py',
                suggest_names / 'suggest.py',
        ],
        output: 'suggest_names_help.txt')

suggest_names_rename_help = custom_target('suggest_names_rename --help',
        command: [
                find_program('env'),
                'COLUMNS=60',
                'python3',
                suggest_names / 'suggest_names_rename',
                '--help'],
        capture: true,
        depend_files: [
                suggest_names / 'suggest_names_rename',
                suggest_names / 'database.py',
                suggest_names / 'merge.py',
                suggest_names / 'suggest.py',
        ],
        output: 'suggest_names_rename_help.txt')

example_varnames_json = custom_target('Example Variable-names Database',
        command: [
                find_program('clang++'),
                '-fplugin=' + dump_names.full_path(),
                '-Xclang',
                '-plugin-arg-dump-names',
                '-Xclang',
                'output-file',
                '-Xclang',
                '-plugin-arg-dump-names',
                '-Xclang',
                '@OUTPUT@',
                '-c',
                '@INPUT@',
                '-fdebug-prefix-map=' + meson.current_build_dir() + '=.',
                '-std=c++11',
                '-o',
                '/dev/null'],
        depends: [
                dump_names
        ],
        input: example_cpp,
        output: 'example.varnames.json')

example_suggestions = custom_target('Example variable name suggestions',
        command: [
                find_program('python3'),
                suggest_names / 'suggest_names',
                example_varnames_json,
                'example.cpp',
                '2',
                '9'
        ],
        depend_files: [
                suggest_names / 'suggest_names',
                suggest_names / 'database.py',
                suggest_names / 'merge.py',
                suggest_names / 'suggest.py',
        ],
        capture: true,
        output: 'example_suggestions',)

example_failure = custom_target('Example variable name suggestion failure',
        command: [
                gettraceback,
                suggest_names / 'suggest_names',
                example_varnames_json,
                'example.cpp',
                '2',
                '10'
        ],
        depend_files: [
                gettraceback,
                suggest_names / 'suggest_names',
                suggest_names / 'database.py',
                suggest_names / 'merge.py',
                suggest_names / 'suggest.py',
        ],
        capture: true,
        output: 'example_failure')

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
            tex_test_list,
            apt_packages,
            llvm_ppa,
            suggest_names_help,
            suggest_names_rename_help,
            example_varnames_json,
            example_suggestions,
            example_failure],
        depend_files: [
            vim_doc,
            schema,
            databasekeywords,
            files([
                'img/elte_logo.eps',
                'tex/titlepage.tex',
                'tex/introduction.tex',
                'tex/user_documentation.tex',
                'tex/developer_documentation.tex',
                'tex/testing.tex',
                'tex/summary.tex',
                'tex/bibliography.bib',
                'tex/appendix.tex'])])

defense = custom_target('Defense pdf',
        command: [
                find_program('rubber'),
                '--pdf',
                '-I' + meson.source_root() / 'tex',
                '-I' + meson.source_root() / 'img',
                '-I' + meson.current_build_dir(),
                '@INPUT@'],
        build_by_default: true,
        input: 'defense.tex',
        output: 'defense.pdf',
        depend_files: [
            'img/elte_logo.eps'
        ])
