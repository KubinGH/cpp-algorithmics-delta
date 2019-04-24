import random
from string import ascii_lowercase
import functools

@functools.lru_cache(maxsize=32)
def sieve(N, lo=1):
    p = [True for _ in range(N+1)]
    p[0] = p[1] = False
    L = []
    for i in range(2, N+1):
        if p[i]:
            if lo <= i:
                L.append(i)
            for x in range(i*i, N+1, i):
                p[x] = False
    return L

@functools.lru_cache(maxsize=32)
def find_loprime(X, P):
    L = sieve(P[1], P[0])
    Y = []
    for x in range(X[0], X[1]+1):
        y = x
        for p in L:
            while x % p == 0:
                x //= p
        if x == 1:
            Y.append(y)
    return Y

class Test:
    def __init__(self, A):
        self.A = A
    def __str__(self):
        return f"{len(self.A)}\n" + " ".join(str(x) for x in self.A)
    @classmethod
    def random(cls, N, X):
        return cls([random.randint(*X) for _ in range(random.randint(*N))])
    @classmethod
    def random_primes(cls, N, X):
        L = sieve(X[1], X[0])
        return cls([random.choice(L) for _ in range(random.randint(*N))])
    @classmethod
    def random_primes_unique(cls, N, X):
        L = sieve(X[1], X[0])
        return cls(random.sample(L, random.randint(*N)))
    @classmethod
    def random_loprime(cls, N, X, P):
        L = find_loprime(X, P)
        return cls([random.choice(L) for _ in range(random.randint(*N))])
    @classmethod
    def random_loprime_unique(cls, N, X, P):
        L = find_loprime(X, P)
        return cls(random.sample(L, random.randint(*N)))


'''
groups = [
    {"group": "0", "count": 3, "args": ((2, 10), (1, 100)), "suf": ascii_lowercase[2:]},
    {"group": "1", "count": 8, "args": ((2, 100), (1, 1000)), "met": [0,0,0,0,1,1,1,1]},
    {"group": "2", "count": 10, "args": ((2, 2048), (1, 5*10**5)), "met": [0,0,0,0,0,0,0,0,1,1]},
    {"group": "3", "count": 6, "args": ((2, 10**5), (1, 5*10**5)), "met": [0,0,0,1,1,1]},
    {"group": "4", "count": 8, "args": ((2, 100), (1, 5*10**5)), "met": [0,0,0,0,1,1,1,1]}
]
'''

def next_group(num, calls, suf=ascii_lowercase):
    for i, (func, args) in enumerate(calls):
        fn = "in/" + str(num) + suf[i] + ".in"
        print(fn)
        t = func(*args)
        with open(fn, "w") as f:
            f.write(str(t))

def tpl_random(N, X):
    return (Test.random, ((2, N), (1, X)))
def tpl_primes(N, X):
    return (Test.random_primes, ((2, N), (1, X)))
def tpl_primes_unique(N, X):
    return (Test.random_primes_unique, ((2, N), (1, X)))
def tpl_loprime(N, X, P):
    return (Test.random_loprime, ((2, N), (1, X), (2, P)))
def tpl_loprime_unique(N, X, P):
    return (Test.random_loprime_unique, ((2, N), (1, X), (2, P)))


random.seed(1337)

next_group(
    0,
    [tpl_random(10, 100), tpl_random(100, 1000), tpl_random(10000, 5*10**5)],
    suf=ascii_lowercase[2:]
)

next_group(
    1,
    [tpl_random(10, 10**6), tpl_random(10, 10**6),
     tpl_primes(10, 10**6), tpl_primes_unique(10, 10**6)]
)

next_group(
    2,
    [tpl_random(100, 1000), tpl_random(100, 1000), tpl_random(100, 1000),
     tpl_primes(150, 1000), tpl_primes(150, 1000), tpl_primes_unique(150, 1000),
     tpl_loprime(100, 1000, 50), tpl_loprime(100, 1000, 50),
     tpl_loprime_unique(100, 1000, 50), tpl_loprime_unique(100, 1000, 50)]
)

next_group(
    3,
    [tpl_random(4000, 10**6), tpl_random(4000, 10**6),
     tpl_primes(4000, 10**6), tpl_primes_unique(4000, 10**6),
     tpl_loprime(4000, 10**6, 100), tpl_loprime_unique(100, 10**6, 100)]
)

next_group(
    4,
    [tpl_random(5*10**4, 10**6), tpl_random(5*10**4, 10**6),
     tpl_primes(5*10**4, 10**6), tpl_primes_unique(5*10**4, 10**6),
     tpl_loprime(5*10**4, 10**6, 500), tpl_loprime_unique(5*10**4, 10**6, 500)]
)

next_group(
    5,
    [tpl_random(10**5, 10**6), tpl_random(10**6, 10**6),
     tpl_primes(10**5, 10**6), tpl_primes_unique(5*10**4, 10**6),
     tpl_loprime(5*10**5, 10**6, 500), tpl_loprime_unique(10**5, 10**6, 500)]
)
