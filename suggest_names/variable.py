class Variable(object):
    def __init__(self, type, name, location):
        self.__type = type
        self.__name = name
        self.__location = location

    @property
    def type(self):
        return self.__type

    @property
    def name(self):
        return self.__name

    @property
    def location(self):
        return self.__location

    def __repr__(self):
        return 'Variable(type=%r, name=%r, location=%r)' % (
                self.__type,
                self.__name,
                self.__location)

    def __eq__(self, other):
        if not isinstance(other, Variable):
            return False
        return (self.__type, self.__name, self.__location) == \
                (other.__type, other.__name, other.__location)

    def __hash__(self):
        return hash((self.__type, self.__name, self.__location))
