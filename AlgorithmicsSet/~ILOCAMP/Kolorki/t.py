import os, random

class Test:
    def __init__(self, n, m):
        self.n, self.m = n, m
    @classmethod
    def random(self, N=10**4, M=60):
        return Test(random.randint(2, N), random.randint(1, M))
    def __str__(self):
        return f"{self.n} {self.m}"
    def call(self, app):
        with open("tmp.in", "w") as f: f.write(str(self))
        os.system(f"{app} < tmp.in > tmp.out 2> NUL")
        return int(open("tmp.out", "r").read().strip())

for _ in range(16):
    T = Test.random()
    print(T)
    got, exp = T.call("kol-beta.exe"), T.call("kol")
    print(">", got)
    print("?", exp)
    assert got == exp
