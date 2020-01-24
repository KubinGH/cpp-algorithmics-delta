import os, subprocess
import random
import itertools

def call_with_io(command, string=""):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=True
    ).stdout.decode()

os.system("rm -i ./ple")
print(call_with_io("mkcxxO ple.cpp ple"))

def powerset(S):
    return itertools.chain.from_iterable(itertools.combinations(S, r) for r in range(len(S)+1))

class Test:
    def __init__(self):
        n = random.randint(1, 20)
        self.A = [random.randint(1, 7) for _ in range(n)]
        q = random.randint(1, 20)
        self.Q = [tuple(sorted((random.randint(1, n), random.randint(1, n)))) + (random.randint(1, 17),) for _ in range(q)]

    def str(self):
        return "{}\n{}\n{}\n{}".format(
            len(self.A), " ".join(str(x) for x in self.A),
            len(self.Q), "\n".join(f"{l} {r} {s}" for l, r, s in self.Q),
        )

    def get(self):
        out = call_with_io("./ple", self.str()).strip().split('\n')
        assert all(x in ("TAK", "NIE") for x in out)
        return [x == "TAK" for x in out]

    def exp(self):
        ret = []
        for l, r, s in self.Q:
            ret.append(any(s == sum(x) for x in powerset(self.A[l-1:r])))
        return ret

for _ in range(1000):
    t = Test()
    print(t.str())
    print(t.get())
    print(t.exp())
    assert t.get() == t.exp()
