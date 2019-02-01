import os, random

class Test:
    def __init__(self, n, P):
        self.n, self.P = n, P
    def __str__(self):
        n, P = self.n, self.P
        return f"{n}\n0.{P[0]:>02} 0.{P[1]:>02} 0.{P[2]:>02} 0.{P[3]:>02} 0.{P[4]:>02}"
    @classmethod
    def random(cls, N=(1, 4), C=(1, 99)):
        n = 5 * random.randint(*N)
        B = [0] + sorted(random.randint(*C) for _ in range(4)) + [100]
        print(B)
        P = [B[i] - B[i-1] for i in range(1, 6)]
        print(P, sum(P))
        return cls(n, P)
    def call(self):
        with open("tmp.in", "w") as f: f.write(str(self))
        os.system("row < tmp.in > tmp.cpp.out")
        os.system("row.py < tmp.in > tmp.py.out")
        opy, ocpp = open("tmp.py.out", "r").read().strip(), open("tmp.cpp.out", "r").read().strip()
        return float(opy), float(ocpp)

for _ in range(128):
    print(_)
    t = Test.random(N=(1, 1))
    print(t)

    rpy, rcpp = t.call()
    print(f" py> {rpy:0.15f}")
    print(f" cpp> {rcpp:0.15f}")
    if abs(rcpp - rpy) > 5*10**-10:
        print("!@#")
        break
