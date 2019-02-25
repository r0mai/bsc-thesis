import json

from variable import Variable

class Database(object):
    def __init__(self):
        self.__variables = {}

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
