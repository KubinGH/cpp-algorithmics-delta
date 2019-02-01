import os, random

class Test:
    def __init__(self, n, m):
        self.n, self.m = n, m
    @classmethod
    def random(cls, B=(1, 2000)):
        return cls(random.randint(*B), random.randint(*B))
    def __str__(self):
        return f"{self.n} {self.m}"
    def call(self):
        with open("tmp.in", "w") as f: f.write(str(self))
        os.system("drz.exe < tmp.in > tmp.got.out 2> NUL")
        os.system("drz-brute.exe < tmp.in > tmp.exp.out 2> NUL")
        got = open("tmp.got.out", "r").read().strip()
        exp = open("tmp.exp.out", "r").read().strip()
        return got, exp


for t in range(10**6):
    T = Test.random((1, 80))
    n, m = T.n, T.m
    got, exp = T.call()
    print(f"{{{t}}} {n}, {m} -> ?'{got}' >'{exp}'")
    assert got == exp

