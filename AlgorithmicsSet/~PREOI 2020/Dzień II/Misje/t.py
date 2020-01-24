import os, subprocess
import random


def call_with_io(command, string=""):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=True
    ).stdout.decode()

N = 5

class Test:
    def __init__(self):
        n = self.n = random.randint(2, N)
        self.m = random.randint(0, n*(n-1))
        self.q = random.randint(1, n*(n-1))
        F = [(u, v) for u in range(n) for v in range(n) if u != v]
        self.E = random.sample(F, self.m)
        self.Q = random.sample(F, self.q)

    def __str__(self):
        return "{} {}\n{}\n{}\n{}".format(self.n, self.m, "\n".join(f"{u+1} {v+1}" for u, v in self.E), self.q, "\n".join(f"{u+1} {v+1}" for u, v in self.Q))

    def get(self):
        ret = call_with_io("./mis", str(self)).strip().split("\n")
        assert all(s in ("MISJA UDANA", "MISJA NIEUDANA") for s in ret)
        return [s == "MISJA UDANA" for s in ret]

    def exp(self):
        G = [[] for _ in range(self.n)]
        for u, v in self.E:
            G[u].append(v)

        def get_reach(s):
            vis = set()
            def dfs(u):
                if u in vis:
                    return
                vis.add(u)
                for v in G[u]:
                    dfs(v)
            dfs(s)
            return [u in vis for u in range(self.n)]

        reach = [get_reach(s) for s in range(self.n)]
        return [reach[u][v] and reach[v][u] for u, v in self.Q]

os.system("rm -i ./mis")
print(call_with_io("mkcxxO mis.cpp mis"))

for _ in range(1000):
    t = Test()
    print(t)
    print(f"got {t.get()}, exp {t.exp()}")
    assert t.get() == t.exp()
