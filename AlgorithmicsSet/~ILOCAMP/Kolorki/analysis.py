import itertools
import collections
from fractions import Fraction as F
import math

def popcount(x):
    return bin(x).count("1")

def Y(m):
    return (2**m - (m+1))

def chi_x(n, m):
    return Y(m)**(n-1) * (n > 1)

def solve(n, m):
    r1 = 0
    r0 = 0 
    v = set()
    z1 = collections.defaultdict(int)
    z0 = collections.defaultdict(int)
    e0 = {2**k: 0 for k in range(m)}
    e00 = 0
    for c in itertools.combinations_with_replacement(range(2**m), n):
        for p in itertools.permutations(c):
            if p in v:
                continue
            v.add(p)
            c1 = all(popcount(p[i] ^ p[(i+1)%n]) > 1 for i in range(n))
            c0 = all(popcount(p[i] ^ p[i+1]) > 1 for i in range(n-1))
            r1 += c1; r0 += c0
            if c1:
                for i in p:
                    z1[i] += 1
            if c0:
                for i in p:
                    z0[i] += 1
                if list(p)[0] == 0:
                    w = list(p)[-1]
                    if w in e0:
                        e0[w] += 1
                    if w == 0:
                        e00 += 1
    print(e0)
    print(e00)
    #assert set(e0.values()) == {chi_x(n, m)} 
    return (r1, r0), (z0, z1)

'''
N = 11

for n in range(4, 20):
    for m in range(3, 20):
        print(chi_x(n, m), math.factorial(m))
        assert chi_x(n, m) % math.factorial(m) == 0 

for m in range(3, 7):
    print(); print()
    v = [(-1, -1) for _ in range(N)]
    z = [({}, {}) for _ in range(N)]
    print(f"m = {m}")
    for n in range(2, N):
        print(f" n = {n}")
        try:
            v[n], z[n] = solve(n, m)
        except KeyboardInterrupt:
            break
    print()
    print(">> results")
    print(v)
    print(">> chi0")
    print([v[n][1] for n in range(2, N)])
    print(">> chi0 formula")
    def chi0(n): return 2**m * chi_x(n, m)
    print([chi0(n) for n in range(2, N)])
    print(">> c1")
    print(">> c0")
    print("1", [-1 if not z[n][1] else list(z[n][1].items())[0][1] for n in range(2, N)])
    print("0", [-1 if not z[n][0] else list(z[n][0].items())[0][1] for n in range(2, N)])
    print(">> c0 formula")
    print("0", [n * (2**m - (m+1))**(n-1) for n in range(2, N)])
    print(">> iota0")
    print([chi0(n-2) for n in range(2, N)])
    print(">> iota1")
    print([chi0(n-1) - chi0(n-3) for n in range(2, N)])
    print(">> chi2")
    print([v[n][1] - v[n][0] for n in range(2, N)])
    print(">> chi2 formula")
    print([(chi_x(n, m) * m + chi0(n-2)) for n in range(2, N)])
    #print(">> fractions")
    #print([(F(*v[n]).numerator, F(*v[n]).denominator)  for n in range(2, 10)])
'''
