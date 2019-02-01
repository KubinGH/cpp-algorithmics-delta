import os
import random

class Test:
    def __init__(self, n, P):
        self.n, self.P = n, P
    @classmethod
    def random(cls, N, C):
        n = random.randint(*N)
        P = set()
        while len(P) < n:
            p = tuple(random.randint(*C) for _ in range(3))
            if p not in P:
                P.add(p)
        return cls(n, P)
    def __str__(self):
        p = "\n".join(" ".join(str(c) for c in t) for t in self.P)
        return f"{self.n}\n{p}"
    def call(self):
        with open("tmp.in", "w") as f: f.write(str(self))
        os.system(f"pod.exe < tmp.in > tmp.got.out 2> NUL")
        os.system(f"pod-brute.exe < tmp.in > tmp.exp.out 2> NUL")
        got = open("tmp.got.out", "r").read().strip()
        exp = open("tmp.exp.out", "r").read().strip()
        return got, exp

for _ in range(128):
    t = Test.random((1, 512), (-8, 8))
    got, exp = t.call()
    print(t)
    print("> got")
    print(got)
    print("$ exp")
    print(exp)
    if got != exp:
        print("!@#")
        z = f"failed{random.randint(0, 2**16-1)}.in"
        print(f"-> {z}")
        with open(z, "w") as f:
            f.write(str(t))
        break
