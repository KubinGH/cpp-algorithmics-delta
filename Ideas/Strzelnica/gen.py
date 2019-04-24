from string import ascii_lowercase
import random

class Test:
    def __init__(self, R, K, L):
        self.R, self.K, self.L = R, K, L
    def __str__(self):
        s = f"{len(self.R)} {len(self.K)} {len(self.L)}\n"
        for r in self.R:
            s += " ".join(str(v) for v in r) + "\n"
        s += " ".join(str(v) for v in self.K) + "\n"
        s += " ".join(str(v) for v in self.L) + "\n"
        return s
    @classmethod
    def random(cls, N, P, C):
        def rc(): return random.randint(*C)
        n, k, l = random.randint(*N), random.randint(*P), random.randint(*P)
        R = []
        while len(R) < n:
            x1, y1, x2, y2 = rc(), rc(), rc(), rc()
            if x1 == x2 or y1 == y2: continue
            if x1 > x2: x1, x2 = x2, x1
            if y1 > y2: y1, y2 = y2, y1
            R.append((x1, y1, x2, y2))
        K = [rc() for _ in range(k)]
        L = [rc() for _ in range(l)]
        return cls(R, K, L)
        
groups = [
    {"group": "0", "count": 4, "args": ((0, 10), (0, 10), (0, 10))},
    {"group": "1", "count": 20, "args": ((0, 1000), (0, 1000), (0, 1000))},
    {"group": "2", "count": 10, "args": ((0, 1000), (0, 1000), (0, 10**9))},
    {"group": "3", "count": 5, "args": ((0, 10**5), (0, 10**5), (0, 10**5))},
    {"group": "4", "count": 5, "args": ((0, 10**5), (0, 10**5), (0, 10**9))}
]

for G in groups:
    for i in range(G["count"]):
        fn = "in/" + G["group"] + ascii_lowercase[i] + ".in"
        print(fn)
        t = Test.random(*G["args"])
        with open(fn, "w") as f:
            f.write(str(t))

def custom_overflow_tiny(n):
    print(n)
    t = Test(
        [(0, 0, 1, 1) for i in range(10**5)],
        [i%2 for i in range(10**5)],
        [i%2 for i in range(10**5)]
    )
    with open(n, "w") as f:
        f.write(str(t))
def custom_overflow_big(n):
    print(n)
    t = Test(
        [(0, 0, 10**9, 10**9) for i in range(10**5)],
        [random.randint(0, 10**9) for i in range(10**5)],
        [random.randint(0, 10**9) for i in range(10**5)]
    )
    with open(n, "w") as f:
        f.write(str(t))

custom_overflow_tiny("in/5a.in")
custom_overflow_big("in/5b.in")
