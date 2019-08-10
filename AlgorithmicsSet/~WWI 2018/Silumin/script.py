import time
import math
import random

optpoints = ([40, 120, 200, 520, 1000], [350, 1880, 3920, 13936, 47340])

def SIL(Z):
    Z = list(Z)
    o = []
    for x in Z:
        for y in Z:
            o.append(x+y)
            o.append(x*y)
    o.sort()
    r = 0
    for i in range(len(o)):
        if i and o[i] != o[i-1]:
            r += 1
    return r

def plotify(funcs, values = [10, 20, 30, 40, 60, 80] + list(range(100, 1001, 100))):
    for i, f in enumerate(funcs):
        plt.plot(values, [SIL(f(v)) for v in values], 'rbgmc'[i])
    o = (optpoints[0].copy(), optpoints[1].copy())
    while o[0][-1] > values[-1]:
        o[0].pop()
        o[1].pop()
    plt.plot(o[0], o[1], 'yx-')

def makesol(funcs):
    N = [40, 120, 200, 520, 1000]
    def minim(n):
        return min([f(n) for f in funcs], key=SIL)
    t = int(time.time())
    with open(f"sol{t}.cpp", "w") as f:
        f.write("""#include <bits/stdc++.h>
using namespace std;
int main()
{
    size_t n;
    cin >> n;
""")
        for n in N:
            s = minim(n)
            p, z, q = optpoints[1][optpoints[0].index(n)], SIL(s), SIL(list(range(1, n+1)))
            print(f"Writing {n}: {p} < [{z}] < {q} -> {round(20 * (q - z) / (q - p), 1)}pts")
            f.write(f'if(n == {n})' + 'cout << "{}";\n'.format(" ".join(str(x) for x in s)))
        f.write("}")

def locoptim(f, steps=1024):
    def g(n, steps=steps):
        r = set(f(n))
        while n*n*steps > 10**8:
            steps -= 100
        s = SIL(r)
        for i in range(steps):
            e = random.randint(0, 22)
            x = random.randint(2**e, 2**(e+1)-1)
            while x in r:
                e = random.randint(0, 22)
                x = random.randint(2**e, 2**(e+1)-1)
            y = random.choice(list(r))
            z = SIL(r ^ {x, y})
            if z < s:
                r ^= {x, y}
                s = z
        return sorted(r)
    return g

def slog2(n):
    r = []
    i = 1
    while len(r) < n:
        r.append(i)
        i += int(math.ceil(max(math.log(max(math.log(i), 1)), 1)))
    return r

def twobits(n):
    r = {2**k | 2**l for k in range(31) for l in range(31)}
    i = 1
    while len(r) < n:
        r.add(i)
        i += 1
    return sorted(r)[:n]

def threebits(n):
    r = {2**k | 2**l | 2**ł for k in range(31) for l in range(31) for ł in range(31)}
    return sorted(r)[:n]
