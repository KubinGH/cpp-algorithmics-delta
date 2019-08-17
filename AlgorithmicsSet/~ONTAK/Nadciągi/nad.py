from functools import lru_cache

mod = 10**9 + 7

gap = 1 << 17
with open("faccache.txt", "r") as file:
    cached_factorials = [int(x) for x in file.read().split(", ") if x]

def ofactorial(n):
    r = 1
    for i in range(1, n+1):
        r *= i
        r %= mod
    return r

@lru_cache(maxsize=None)
def factorial(n):
    r = cached_factorials[n // gap]
    for i in range(max(n - n%gap, 1), n+1):
        r = (r * i) % mod
    return r

def inverse(x):
    return pow(x, mod - 2, mod)

def choose(n, k):
    return factorial(n) * inverse(factorial(k) * factorial(n - k)) % mod

def Ω(n, m, a):
    result = 0
    fn = fk = factorial(n - 1)
    fd = 1
    for k in range(n, m+1):
        result += fk * inverse(fn * fd) * pow(a-1, k-n, mod) * pow(a, m-k, mod)
        fd *= k - n + 1; fd %= mod
        fk *= k; fk %= mod
        result %= mod
    return result

def o_succ(n, m, a, value):
    return (a*value + choose(m, n - 1) * pow(a-1, m-n+1, mod)) % mod

@lru_cache(maxsize=None)
def O(n, m, a):
    #print(f"O({n}, {m}, {a})")
    if n >= m:
        return n == m
    if n > m//2:
        #print(f"Ω({n}, {m}, {a})")
        return Ω(n, m, a)

    result = 0
    for i in range(n+1):
        x = O(i, m//2, a)
        y = O(n - i, m//2, a)
        if m % 2:
            y = o_succ(n - 1, m//2, a, y)
        result += x * y

    return result % mod
