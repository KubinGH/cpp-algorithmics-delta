# WolframAlpha is a great tool.
# inny sposób interpolacji: numpy.linalg.solve albo wielomian Legrenge'a.

class iPolynomial:
    def __init__(self, *coeff, div=1):
        self.coeff = coeff
        self.div = div
    @property
    def degree(self):
        return len(self.coeff) - 1
    def evaluate(self, x):
        return sum(c * x**(self.degree - i) for i, c in enumerate(self.coeff)) // self.div
    def __str__(self):
        return " + ".join(f"{c}/{self.div} x^{self.degree - i}" for i, c in enumerate(self.coeff))
    @classmethod
    def interpolate(cls, *P):
        degree = len(P) - 1
        if degree == 0:
            return cls(P[0])
        elif degree == 1:
            return cls(P[1] - P[0], P[0])
        elif degree == 2:
            return cls(P[2] - 2*P[1], 4*P[1] - P[2], 2*P[0], div=2)
        elif degree == 3:
            return cls(-P[0] + 3*P[1] - 3*P[2] + P[3], 6*P[0] - 15*P[1] + 12*P[2] - 3*P[3],
                       -11*P[0] + 18*P[1] - 9*P[2] + 2*P[3], 6*P[0], div=6)
        elif degree == 4:
            return cls(
                P[0] - 4*P[1] + 6*P[2] - 4*P[3] + P[4],
                -10*P[0] + 36*P[1] - 48*P[2] + 28*P[3] - 6*P[4],
                35*P[0] - 104*P[1] + 114*P[2] - 56*P[3] + 11*P[4],
                -50*P[0] + 96*P[1] - 72*P[2] + 32*P[3] - 6*P[4],
                24*P[0],
                div=24
            )
        else:
            raise ValueError("Unknown interpolation method for degree {}".format(degree))


P = iPolynomial.interpolate(1, 3, 6)
print([P.evaluate(x) for x in range(10)])
