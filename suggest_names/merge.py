from database import Database


def merge_databases(databases):
    variables = merge_variables([database.variables for database in databases])
    return Database(variables=variables)


def merge_variables(variableses):
    all_variables = {
        variable for variables in variableses for variable in variables}
    return all_variables
