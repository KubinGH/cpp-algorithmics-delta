from functools import lru_cache

n, a, b = [int(x) for x in input().split()]

@lru_cache(maxsize=None)
def f(m, s):
    if m == 0:
        return s == 0
    elif s <= 0:
        return 0
    else:
        return sum(f(m - 1, s - k) for k in range(1, 7))

total = sum(f(n, c) for c in range(n, 6*n + 1))
oks = sum(f(n, c) for c in range(a, b + 1))

print(f"{oks / total:.6f}")
