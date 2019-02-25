import json

from variable import Variable

class Database(object):
    def __init__(self, variables={}):
        self.__variables = variables

    @staticmethod
    def load_from_file(filename):
        d = json.load(open(filename))
        db = Database()
        db.__variables = {
            Variable(
                type=variable["type"],
                name=variable["name"],
                location=variable["location"])
            for variable in d["Variables"]
        }
        return db

    @property
    def variables(self):
        return self.__variables

    def __repr__(self):
        return 'Database(variables=%r)' % (self.__variables)

    def __eq__(self, other):
        if not isinstance(other, Database):
            return False
        return (self.__variables) == (other.__variables)

    def __hash__(self):
        return hash((self.__variables))
