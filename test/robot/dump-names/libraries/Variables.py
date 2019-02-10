import json

class Variables(object):
    def __init__(self):
        pass

    def load_variables_from_analysis(self, content):
        d = json.loads(content)
        return d['Variables']
