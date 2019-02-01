import os, random

class Test:
    def __init__(self, A, Q):
        self.A, self.Q = A, Q
    def __str__(self):
        sA = " ".join(str(x) for x in self.A)
        sQ = "\n".join(" ".join(str(x) for x in q) for q in self.Q)
        return f"{len(self.A)} {len(self.Q)}\n{sA}\n{sQ}"
    @classmethod
    def random(cls, nB, qB, B):
        n, q = random.randint(*nB), random.randint(*qB)
        A = [random.randint(*B) for _ in range(n)]
        Q = []
        for _ in range(q):
            t = random.randint(0, 1)
            a, b = sorted([random.randint(1, n), random.randint(1, n)])
            if t == 0:
                Q.append([0, a, b, random.randint(*B)])
            else:
                Q.append([1, a, b])
        return cls(A, Q)
    def call(self):
        import time
        with open("tmp.in", "w") as f: f.write(str(self))
        start = time.time()
        os.system(f"bud.exe < tmp.in > tmp.got.out 2> NUL")
        finish = time.time()
        print(round(finish - start, 3))
        os.system(f"bud-brute.exe < tmp.in > tmp.exp.out 2> NUL")
        got = open("tmp.got.out", "r").read().strip()
        exp = open("tmp.exp.out", "r").read().strip()
        return got, exp

#Test.random((2*10**5, 2*10**5), (2*10**5, 2*10**5), (1, 10**9)).call()

for _ in range(4):
    print(_)
    t = Test.random((1, 2*10**5), (1, 2*10**5), (1, 10**9))
    got, exp = t.call()
    #print(t)
    #print("> got")
    #print(got)
    #print("$ exp")
    #print(exp)
    if got != exp:
        print("!@#")
        z = f"failed{random.randint(0, 2**16-1)}.in"
        print(f"-> {z}")
        with open(z, "w") as f:
            f.write(str(t))
        break

