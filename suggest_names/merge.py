from database import Database


def merge_databases(databases):
    return {
        "Variables":
            merge_variables([database.variables for database in databases])
    }


def merge_variables(variableses):
    all_variables = {
        variable for variables in variableses for variable in variables}
    return all_variables
