import variable
import database
import merge
import suggest

def make_variable(type, name, location, occurences={}):
    return variable.Variable(type, name, location, occurences)

def make_database(*variables, filename="/dev/zero"):
    return database.Database(variables={*variables}, filename=filename)

def merge_databases(databases):
    return merge.merge_databases(databases)

def make_suggestions(database, variable):
    return suggest.suggest_for(database, variable)
