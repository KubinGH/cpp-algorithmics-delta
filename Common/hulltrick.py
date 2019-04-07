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

def build_line_convex_hull(lines):
    def covered(A, B, C):
        # C covered by A and B
        return (A ^ B) >= (B ^ C)
    lines.sort(key=lambda k: (-k.a, -k.b))
    hull = []
    a = None
    for C in lines:
        if C.a == a: continue
        a = C.a
        while len(hull) >= 2:
            A, B = hull[-2:]
            print(A, B, C)
            if not covered(A, B, C):
                break
            else:
                hull.pop()
        hull.append(C)
    return hull

def find_min_line(hull, x):
    lo, hi = 0, len(hull)
    while lo < hi:
        mid = (lo + hi) // 2
        if mid+1 == len(hull) or hull[mid](x) < hull[mid+1](x):
            hi = mid
        else:
            lo = mid+1
    return lo

hull = build_line_convex_hull([Line(2, 3), Line(2, 2), Line(1, 1), Line(5, 0), Line(-1, 10)])

print(hull)
print("x = -1:", find_min_line(hull, -1))
print("x = 3:", find_min_line(hull, 3))
print("x = 8:", find_min_line(hull, 8))
