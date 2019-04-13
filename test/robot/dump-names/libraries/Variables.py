import json
import jsonschema
import os

class Variables(object):
    def __init__(self):
        self.schema = json.load(open(
                os.path.join(os.path.dirname(__file__),
                        '..', '..', '..', '..', 'schema', 'varnames.json')))

    def load_variables_from_analysis(self, content):
        d = json.loads(content)
        jsonschema.validate(instance=d, schema=self.schema)
        return d['Variables']
