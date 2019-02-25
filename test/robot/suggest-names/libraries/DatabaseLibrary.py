import variable
import database
import merge


def make_variable(type, name, location):
    return variable.Variable(type, name, location)

def make_database(*variables):
    return database.Database(variables={*variables})

def merge_databases(databases):
    return merge.merge_databases(databases)
