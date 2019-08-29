import z8

class Foo:
    def __le__(self, other):
        return False
    def __ge__(self, other):
        return False
    def __lt__(self, other):
        return False
    def __gt__(self, other):
        return False
    def __eq__(self, other):
        return False
    def __ne__(self, other):
        return False

z8.fun(Foo())
