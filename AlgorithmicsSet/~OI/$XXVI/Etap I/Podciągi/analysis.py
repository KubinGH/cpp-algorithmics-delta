import sympy
from sympy.abc import a, b, c, d, e, f, g, h, i, j, k, l, p, q, r, s, n, x, y
import collections
import time

def interpret_template(T):
    ls = collections.defaultdict(int)
    dp = [0 for _ in range(len(T)+2)]
    dp[0] = 0; dp[1] = 1
    for i, v in enumerate(T):
        if isinstance(v, set):
            v = next(iter(v))
            dp[i+2] = dp[i+1] * v
        elif isinstance(v, tuple):
            v, p = v
            d = dp[i+1] - ls[v]
            dp[i+2] = dp[i+1] + p * d
            ls[v] = dp[i+1] + (p - 1) * d
        else:
            dp[i+2] = 2*dp[i+1] - ls[v]
            ls[v] = dp[i+1]
    return dp[-1]

# a -> letter
# {r} -> word with given C value = r
# (a, p) -> letter a repeated p times

print(sympy.factor(interpret_template("abcefhijklmnoopqrtuvwxyzABCDDEEEEEEDDDDAxwwwvutssrpoooommmkiiighggedd")))

exit()

T = interpret_template([(x, a), (y, b), {r}, (x, c), (y, d), (x, e), (y, f)])
print(sympy.factor(T))
print(sympy.solveset(T - n, r))

congo = set()
lastc = None

def handle(S):
    P = sympy.poly(S)
    ż, z = P.coeffs()[0], P.coeffs()[1]%P.coeffs()[0] if len(P.coeffs()) > 1 else 0
    congo.add((int(ż), int(z)))
    global lastc
    lastc = (int(ż), int(z))

for _a in range(6):
    for _b in range(6):
        print(_a, _b)
        for _c in range(6):
            for _d in range(6):
                for _e in range(6):
                    for _f in range(6):
                        handle(T.subs([(a, _a), (b, _b), (c, _c), (d, _d), (e, _e), (f, _f)]))
                        if (_a, _b, _c, _d, _e, _f) == (1, 2, 3, 2, 1, 0):
                            print(lastc)
congo.discard((1, 0))

#with open("pairs.txt", "w") as file:
#    for c in sorted(congo):
#        file.write(f"{c[0]} {c[1]}\n")

print("congruences", len(congo))
bykey = {k: set() for k in {c[0] for c in congo}}
for c in congo:
    bykey[c[0]].add(c[1])
print("keys", len(bykey))

from fractions import Fraction
P = Fraction(1, 1)
for k in bykey:
    P *= Fraction((k - len(bykey[k]) + int(0 in bykey[k])), k)
print("probability", P)

from random import randint
for _ in range(2**26):
    if _ % (2**14) == 0: print(_)
    i = randint(1, 10**18//4)*4 + 1
    for k in bykey:
        if i%k in bykey[k]:
            #print(f"{i} ≡ {i%k} (mod {k})")
            break
    else:
        print(f"{i} ??")
        break
