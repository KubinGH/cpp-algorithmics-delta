from collections import deque
import sys

class Line:
    def __init__(self, a, b):
        self.a, self.b = a, b

def hull_append(hull, C):
    def line_covered(A, B):
        # C covered by A and B
        return (B.a == C.a and B.b >= C.b) or (B.b - A.b) * (B.a - C.a) <= (C.b - B.b) * (A.a - A.b)
    while len(hull) >= 2:
        A, B = hull[-1], hull[-2]
        if not line_covered(A, B):
            break
        else:
            hull.pop()
    hull.append(C)

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
    return hull[find_min_line(hull, x)](x)
    
n = int(next(sys.stdin))

R = []

for i in range(n):
    x, y, a = [int(x) for x in next(sys.stdin).split(" ")]
    R.append((x, y, a))

R.sort()

Q = [0 for _ in range(n+1)]
hull = [Line(0, 0)]

p = 0

for i in range(n):
    while not (p+1 == len(hull) or (hull[p].a*R[i][1]+hull[p].b) < (hull[p+1].a*R[i][1]+hull[p+1].b)):
        p += 1
    Q[i+1] = R[i][0]*R[i][1] - (hull[p].a*R[i][1] + hull[p].b) - R[i][2]
    hull_append(hull, Line(R[i][0], -Q[i+1]))

print(max(Q))
