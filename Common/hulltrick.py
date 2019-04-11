from fractions import Fraction

class Line:
    def __init__(self, a, b):
        self.a, self.b = a, b
    def __xor__(self, other):
        return Fraction(other.b - self.b, self.a - other.a)
    def __call__(self, x):
        return self.a * x + self.b
    def __repr__(self):
        return "Line({}, {})".format(self.a, self.b)


def hull_append(hull, C):
    def line_covered(A, B):
        # C covered by A and B
        return (B.a == C.a and B.b >= C.b) or (A ^ B) >= (B ^ C)
    while len(hull) >= 2:
        A, B = hull[-2], hull[-1]
        if not line_covered(A, B):
            break
        else:
            hull.pop()
    hull.append(C)

def hull_appendleft(hull, C):    
    def line_covered(A, B):
        # C covered by A and B
        return (B.a == C.a and B.b >= C.b) or (A ^ B) <= (B ^ C)
    while len(hull) >= 2:
        A, B = hull[0], hull[1]
        if not line_covered(A, B):
            break
        else:
            hull.popleft()
    hull.appendleft(C)

def find_min_line(hull, x):
    lo, hi = 0, len(hull)
    while lo < hi:
        mid = (lo + hi) // 2
        if mid+1 == len(hull) or hull[mid](x) < hull[mid+1](x):
            hi = mid
        else:
            lo = mid+1
    return lo

def find_min_line_value(hull, x):
    return hull[find_min_line(hull, x)](x)s

hull = build_line_convex_hull([Line(2, 3), Line(2, 2), Line(1, 1), Line(5, 0), Line(-1, 10)])

print(hull)
print("x = -1:", find_min_line(hull, -1))
print("x = 3:", find_min_line(hull, 3))
print("x = 8:", find_min_line(hull, 8))
