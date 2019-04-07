import math
try:
    import numpy
except ImportError:
    NUMPY_ENABLED = False
else:
    NUMPY_ENABLED = True

MOD = 10**9 + 7

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
        if NUMPY_ENABLED:
            equations = [
                [x**k for k in range(degree, -1, -1)]
                for x in range(len(P))
            ]
            values = [math.factorial(degree) * y for y in P]
            coeff_fp = numpy.linalg.solve(equations, values)
            coeff = [int(round(c)) for c in coeff_fp]
            return cls(*coeff, div=math.factorial(degree))
        else:
            if degree == 0:
                return cls(P[0])
            elif degree == 1:
                return cls(P[1] - P[0], P[0])
            elif degree == 2:
                return cls(P[0] - 2*P[1] + P[2], -3*P[0] + 4*P[1] - P[2], 2*P[0], div=2)
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

def at(x, y):
    s = max(abs(x), abs(y))
    if (x, y) == (s, -s):
        return (2*s+1)**2
    if x == s:
        return (2*s-1)**2 + 1 + y + (s-1)
    elif y == s:
        return (2*s-1)**2 + 2*s + (s-x) 
    elif x == -s:
        return (2*s-1)**2 + 4*s + (s-y)
    elif y == -s:
        return (2*s-1)**2 + 6*s + (x+s)

def partial_sums(L):
    return ([L[0]] + [d + L[0] for d in partial_sums(L[1:])]) if L else []

def quarter_general(x, y, dx, dy, sx, sy, I=iPolynomial.interpolate, E=partial_sums):
    if x < 0 or y < 0: return 0
    # squares are made of L-shapes
    r = I(*E([
        sum(at(z*dx, i*dy) + at(i*dx, z*dy) for i in range(z)) + at(z*dx, z*dy) for z in range(5)
    ])).evaluate(min(x, y))
    if x < y:
        # rows
        r += I(*E([
                I(*E((at(0, y1*dy), at(0, y1*dy)+sx, at(0, y1*dy)+2*sx))).evaluate(x)
                for y1 in range(x+1, x+5)
        ])).evaluate(y-x-1)
    elif y < x:
        # columns
        r += I(*E([
                I(*E((at(x1*dx, 0), at(x1*dx, 0)+sy, at(x1*dx, 0)+2*sy))).evaluate(y)
                for x1 in range(y+1, y+5)
        ])).evaluate(x-y-1)
    return r

def quarter1(x, y, I=iPolynomial.interpolate, E=partial_sums):
    return quarter_general(x, y, 1, 1, -1, 1)

def quarter2(x, y, I=iPolynomial.interpolate, E=partial_sums):
    return quarter_general(x, y, -1, 1, 1, -1)

def quarter3(x, y, I=iPolynomial.interpolate, E=partial_sums):
    return quarter_general(x, y, -1, -1, -1, 1)

def quarter4(x, y, I=iPolynomial.interpolate, E=partial_sums):
    return quarter_general(x, y, 1, -1, 1, -1)

class Rect:
    def __init__(self, x1, y1, x2, y2):
        self.x1, self.y1, self.x2, self.y2 = x1, y1, x2, y2
    @property
    def degenerate(self):
        return self.x1 <= self.x2 and self.y1 <= self.y2
    def __and__(self, other):
        return Rect(max(self.x1, other.x1), max(self.y1, other.y1),
                    min(self.x2, other.x2), min(self.y2, other.y2))

def IE_rect_sum(x1, y1, x2, y2, f):
    return f(x2, y2) - f(x1-1, y2) - f(x2, y1-1) + f(x1-1, y1-1) if x1 <= x2 and y1 <= y2 else 0

def irect(x1, y1, x2, y2):
    return IE_rect_sum(max(x1, 0), max(y1, 1), x2, y2, quarter1) + \
           IE_rect_sum(max(-x2, 1), max(y1, 0), -x1, y2, quarter2) + \
           IE_rect_sum(max(-x2, 0), max(-y2, 1), -x1, -y1, quarter3) + \
           IE_rect_sum(max(x1, 1), max(-y2, 0), x2,  -y1, quarter4) + \
           (x1 <= 0 <= x2 and y1 <= 0 <= y2)

n, q = [int(x) for x in input().split()]

for i in range(q):
    x1, y1, x2, y2 = [int(x) for x in input().split()]
    print(irect(x1, y1, x2, y2) % MOD)
