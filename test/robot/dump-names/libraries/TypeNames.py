import json

class TypeNames(object):
    def __init__(self):
        pass

    def load_typenames_from_analysis(self, content):
        d = json.loads(content)
        return d['TypeNames']
