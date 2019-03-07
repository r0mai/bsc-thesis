class Variable(object):
    def __init__(self, type, name, location, occurences):
        self.__type = type
        self.__name = name
        self.__location = location
        self.__occurences = set(occurences)

    @property
    def type(self):
        return self.__type

    @property
    def name(self):
        return self.__name

    @property
    def location(self):
        return self.__location

    @property
    def occurences(self):
        return self.__occurences

    def can_merge(self, other):
        return (self.__type, self.__name, self.__location) == \
                (other.__type, other.__name, other.__location)

    @staticmethod
    def merge(l, r):
        assert(l.can_merge(r))
        loccurences = l.occurences
        roccurences = l.occurences
        return Variable(type=l.type,
                name=l.name,
                location=l.location,
                occurences=l.occurences.union(r.occurences))

    def __repr__(self):
        return 'Variable(type=%r, name=%r, location=%r, occurences=%r)' % (
                self.__type,
                self.__name,
                self.__location,
                self.__occurences)

    def __eq__(self, other):
        if not isinstance(other, Variable):
            return False
        return self.can_merge(other) and \
                self.__occurences == other.__occurences

    def __hash__(self):
        return hash((self.__type, self.__name, self.__location))
