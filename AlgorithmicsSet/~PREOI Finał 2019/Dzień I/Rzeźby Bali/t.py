import random
from gamma import call_with_io

class Test:
    def __init__(self, Y, a, b):
        self.Y, self.a, self.b = Y, a, b
    @classmethod
    def random(cls, N, E):
        n = random.randint(*N)
        a, b = sorted(random.sample(range(1, n+1), 2))
        return cls([random.randint(*E) for _ in range(n)], a, b)
    def __str__(self):
        return "{} {} {}\n{}".format(len(self.Y), self.a, self.b, " ".join(str(y) for y in self.Y))

for _ in range(1024):
    T = Test.random((2, 100), (0, 10**9))

    r2 = int(call_with_io("rze-n3", str(T)).strip())
    print(">", r2)

    #print(r1, r2)
    #if r1 != r2 or r1 > 2**50:
    #    with open("failed{}.in".format(random.randint(0, 2**16 - 1)), "w") as f:
    #        f.write(str(T))
    #    print("!@#")
    #    break
