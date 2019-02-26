import database

import operator

def get_candidate_variable_names(merged_database, requested_variable):
    result = {}
    for variable in merged_database.variables:
        if variable.type == requested_variable.type:
            if variable.name in result:
                result[variable.name] += 1
            else:
                result[variable.name] = 1
    return result


def suggest_for(merged_database, requested_variable):
    candidates = get_candidate_variable_names(
        merged_database, requested_variable)
    results = []
    for name, count in sorted(
            candidates.items(), key=operator.itemgetter(1),
            reverse=True):
        results.append(name)
    return results

