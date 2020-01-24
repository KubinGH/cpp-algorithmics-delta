import os, subprocess
import random
import itertools

def call_with_io(command, string=""):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=True
    ).stdout.decode()

#os.system("rm -i ./pat")
print(call_with_io("mkcxxO pat.cpp pat"))
#os.system("rm -i ./patbb")
print(call_with_io("mkcxxO patbb.cpp patbb"))

input()

class Test:
    def __init__(self):
        n = random.randint(1, 30)
        m = random.randint(1, 30)
        q = random.randint(1, 30)
        self.E = [(random.randint(0, i-1), random.choice("ab")) for i in range(1, n+1)]
        self.S = "".join(random.choice("ab") for _ in range(m))
        self.Q = [tuple(sorted((random.randint(1, m), random.randint(1, m)))) for _ in range(q)]

    def str(self):
        return "{} {} {}\n{}\n{}\n{}".format(
            len(self.E), len(self.S), len(self.Q),
            "\n".join(" ".join(str(x) for x in p) for p in self.E),
            self.S,
            "\n".join(" ".join(str(x) for x in p) for p in self.Q)
        )

    def get(self):
        out = call_with_io("./pat", self.str()).strip().split('\n')
        return [[int(y) for y in x.split()] for x in out]

    def exp(self):
        out = call_with_io("./patbb", self.str()).strip().split('\n')
        return [[int(y) for y in x.split()] for x in out]

for _ in range(1000):
    t = Test()
    print(t.str())
    print(t.get())
    print(t.exp())
    assert t.get() == t.exp()
