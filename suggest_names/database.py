import json

from variable import Variable

class Database(object):
    def __init__(self, variables={}, filename=""):
        self.__variables = variables
        self.__filename = filename

    @staticmethod
    def load_from_file(file):
        d = json.load(file)
        db = Database()
        db.__variables = {
            Variable(
                type=variable["type"],
                name=variable["name"],
                location=variable["location"],
                occurences=variable["occurences"])
            for variable in d["Variables"]
        }
        db.__filename = d["Filename"]
        return db

    @property
    def variables(self):
        return self.__variables

    @property
    def filename(self):
        return self.__filename

    def __repr__(self):
        return 'Database(variables=%r)' % (self.__variables)

    def __eq__(self, other):
        if not isinstance(other, Database):
            return False
        return (self.__variables) == (other.__variables)

    def __hash__(self):
        return hash((self.__variables))
