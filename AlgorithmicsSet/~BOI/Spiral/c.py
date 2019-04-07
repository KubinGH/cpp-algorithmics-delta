MOD = 10**9 + 7

def sigma(a, b, n):
    # return sum(a + b*i for i in range(n))
    return a*n + b*n*(n-1)//2

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

def cut(a, b, c, d):
    x, y = max(c, a), min(b, d)
    if x <= y:
        return y - x + 1
    else:
        return 0

def rowm(x1, x2, y):
    return sum(at(x, y) for x in range(x1, x2+1)) if x1 <= x2 else 0

def interpolate_cubic(a1, a2, a3, a4):
    return (a4 - a1 + 3*a2 - 3*a3), 3*(-a4 + 2*a1 - 5*a2 + 4*a3), (2*a4 - 11*a1 + 18*a2 - 9*a3), 6*a1
 
def cubic(a, b, c, d, x):
    return (a*x**3 + b*x**2 + c*x + d) // 6

def rowd(x1, x2, y):
    if x1 > x2:
        return 0
    if x2 < -abs(y):
        t1, t2, t3, t4 = at(x2, y), at(x2-1, y), at(x2-2, y), at(x2-3, y)
    elif abs(y) < x1:
        t1, t2, t3, t4 = at(x1, y), at(x1+1, y), at(x1+2, y), at(x1+3, y)
    a, b, c, d = interpolate_cubic(t1, t1+t2, t1+t2+t3, t1+t2+t3+t4)
    r = cubic(a, b, c, d, x2 - x1)
    return r

def row(x1, x2, y):
    r = 0
    if y >= 0:
        r += sigma(at(min(y, x2), y), 1, cut(x1, x2, -y, y))
        r += rowd(x1, min(x2, -y-1), y) + rowd(max(x1, y+1), x2, y)
    else:
        y = -y
        r += sigma(at(max(-y, x1), -y), 1, cut(x1, x2, -y, y))
        r += rowd(x1, min(x2, -y-1), -y) + rowd(max(x1, y+1), x2, -y)
    return r

def query(x1, y1, x2, y2):
    r = 0
    for y in range(y1, y2+1):
        r += row(x1, x2, y)
    print(r % (10**9 + 7))
    return r


import random
from gamma import call_with_io

for i in range(32):
    print(i)
    x1, x2 = sorted((random.randint(-10, 10), random.randint(-10, 10)))
    y1, y2 = sorted((random.randint(-10, 10), random.randint(-10, 10)))
    s1 = query(x1, y1, x2, y2) % (10**9 + 7)
    s2 = int(call_with_io("spiral-beta.py", "100000 1\n{} {} {} {}".format(x1, y1, x2, y2)))
    print(x1, y1, x2, y2, "->", s1, s2)
    assert s1 == s2
