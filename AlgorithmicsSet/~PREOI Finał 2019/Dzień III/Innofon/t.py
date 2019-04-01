from gamma import call_with_io
import random

class Test:
    def __init__(self, P):
        self.P = P
    @classmethod
    def random(cls, N, E):
        return cls([tuple(sorted((random.randint(*E), random.randint(*E)), reverse=True)) for _ in range(random.randint(*N))])
    def __str__(self):
        s = f"{len(self.P)}\n"
        for a, b in self.P:
            s += f"{a} {b}\n"
        return s.strip()

for i in range(32):
    print("$", i)
    T = Test.random((1, 300), (0, 10**9))
    exp = call_with_io("b-n3", str(T))
    got = call_with_io("b", str(T))
    if got != exp:
        print("!@#")
        print(T)
        print(">>>", got, exp)
        with open(f"failed{random.randint(0, 2**16 - 1)}.in", "w") as f:
            f.write(str(T))
        break

