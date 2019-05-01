from database import Database
from variable import Variable

import itertools
import os


def merge_databases(databases):
    current_databases = [database for database in databases if
            os.path.exists(database.filename)]
    variables = merge_variables(
            [database.variables for database in current_databases])
    return Database(variables=variables)


def merge_variables(variableses):
    all_unmerged_variables = {
        variable for variables in variableses for variable in variables}
    key_function = lambda v: (v.type, v.name, v.location)
    all_variables = set()
    data = sorted(all_unmerged_variables, key=key_function)
    for k, g in itertools.groupby(data, key_function):
        result_variable = Variable(*k, set())
        for variable in g:
            assert(result_variable.can_merge(variable))
            result_variable = Variable.merge(result_variable, variable)
        all_variables.add(result_variable)
    return all_variables
