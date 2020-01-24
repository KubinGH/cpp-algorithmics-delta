import os, subprocess
import random
import functools

def call_with_io(command, string):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=True
    ).stdout.decode()

os.system("mkcxx pos.cpp pos")

def product(it, m=0):
    def f(x): return x % m if m else x
    return f(functools.reduce(lambda a, b: f(a*b) if m else a*b, it, 1))

class Test:
    def __init__(self):
        N = 100
        A = 1000
        n, q = random.randint(1, N), random.randint(1, N)
        self.m = random.randint(1, A)
        self.a = [random.randint(0, A) for _ in range(n)]
        self.o = []
        for _ in range(q):
            c = random.randint(0, 1)
            if c == 0:
                self.o.append((0, (random.randint(1, n), random.randint(0, A))))
            else:
                self.o.append((1, random.sample(range(1, n+1), random.randint(0, n - 1))))

    def repr_op(self, op):
        c, d = op
        if c == 0:
            return f"{c} {d[0]} {d[1]}"
        else:
            return "{} {} {}".format(c, len(d), " ".join(str(x) for x in d))

    def str(self):
        return "{} {} {}\n{}\n{}".format(
            len(self.a), self.m, len(self.o), " ".join(str(x) for x in self.a),
            "\n".join(self.repr_op(op) for op in self.o)
        )
    def get(self):
        return [int(x) for x in call_with_io("./pos" , self.str()).strip().split()]
    def exp(self):
        a = self.a.copy()
        result = []
        for c, d in self.o:
            if c == 0:
                p, v = d
                a[p-1] = v
            elif c == 1:
                d = {p-1 for p in d}
                result.append(product((x for i, x in enumerate(a) if i not in d), self.m))
            else:
                assert False
        return result


for _ in range(10**6):
    t = Test()
    print(t.str())
    print(t.get())
    print(t.exp())
    assert t.get() == t.exp()
