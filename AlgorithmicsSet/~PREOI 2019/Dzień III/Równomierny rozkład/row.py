import decimal, functools, decimal, math

def solve(n, P):
    @functools.lru_cache(maxsize=None)
    def Q(p):
        if p == tuple(0 for _ in range(5)):
            return 1
        else:
            r = 0
            for i in range(5):
                if p[i]:
                    p1 = tuple(p[j] - (i==j) for j in range(5))
                    r += P[i] * Q(p1)
            return r

    x, y = Q(tuple(n//5 for _ in range(5))), 100**n
    x, y = x // math.gcd(x, y), y // math.gcd(x, y)
    xd, yd = decimal.Decimal(x), decimal.Decimal(y)
    return xd / yd

n = int(input())
P = [int(x[2:]) for x in input().strip().split()]
print(f"{solve(n, P):.20f}")
