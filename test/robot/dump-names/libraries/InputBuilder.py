class InputBuilder(object):
    def __init__(self):
        pass

    def _get_file_header(self):
        return 'int main() {\n'

    def _get_file_footer(self):
        return '\n}\n'

    def _get_variable_declaration(self, variable_type, variable_name):
        return '{\n' + variable_type + ' ' + variable_name + ';\n}'

    def get_source(self, typeNames):
        output = self._get_file_header()

        output += '\n'.join([self._get_variable_declaration(
                variable_type, variable_name) for variable_name, variable_type
                in typeNames.items()])
        return output + self._get_file_footer()
