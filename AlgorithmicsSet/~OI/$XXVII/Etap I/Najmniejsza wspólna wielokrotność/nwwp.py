import math
import functools
import itertools
import collections
import operator
import sys

M = 10**18
oo2 = (2**64 - 1, 2**64 - 1)

debug = False

def lcm(a, b):
    return a*b // math.gcd(a, b)

def rlcm(a, k):
    return functools.reduce(lcm, range(a, a + k), 1)

def OO2(): return oo2
ok = collections.defaultdict(OO2)

import os, pickle
if os.path.exists("prenww"):
    ok = pickle.load(open("prenww", "rb"))
else:
    for k in itertools.count(4):
        if 2**(k - 1) > M:
            break
        f = g = math.factorial(k)
        for a in itertools.count(1):
            if g > M*f:
                break
            l = rlcm(a, k)
            if l <= M:
                ok[l] = min(ok[l], (a, a + k))
            g //= a
            g *= a+k
    pickle.dump(ok, open("prenww", "wb"))

def F2(n):
    lo = 0
    hi = math.ceil(2*n**0.51)+0xD
    while lo < hi:
        mid = (lo + hi) // 2
        if mid*(mid+1) >= n:
            hi = mid
        else:
            lo = mid+1
    return lo
def F3(n):
    lo = 0
    hi = math.ceil(2*n**0.34+1)+0xD
    while lo < hi:
        mid = (lo + hi) // 2
        if mid*(mid+1)*(mid+2) >= n:
            hi = mid
        else:
            lo = mid+1
    return lo

input = sys.stdin.read()
no = [int(x) for x in input.split()]

q = no[0]

out = []
for i in range(q):
    n = no[i+1]

    a = F2(n)
    l = rlcm(a, 2)
    ok[l] = min(ok[l], (a, a + 2))

    a = F3(n)
    l = rlcm(a, 3)
    ok[l] = min(ok[l], (a, a + 3))

    a = F3(2*n)
    l = rlcm(a, 3)
    ok[l] = min(ok[l], (a, a + 3))

    if ok[n] != oo2:
        a, b = ok[n]
        out.append(str(a) + " " + str(b - 1))
    else:
        pass
        out.append("NIE")

print("\n".join(out))
