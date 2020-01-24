import os, subprocess
import random

def call_with_io(command, string):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=True
    ).stdout.decode()

class Test:
    def __init__(self):
        n = random.randint(1, 200)
        self.A = [tuple(sorted(random.sample([x*10**7 for x in range(1, 20)], 2))) for _ in range(n)]

    def str(self):
        return "{}\n{}".format(len(self.A), "\n".join(f"{a} {b}" for a, b in self.A))

    def get(self):
        out = call_with_io("./szk", self.str()).strip().split()
        assert all(x in ("TAK", "NIE") for x in out)
        return [x == "TAK" for x in out]

    def exp(self):
        out = call_with_io("./szkb", self.str()).strip().split()
        assert all(x in ("TAK", "NIE") for x in out)
        return [x == "TAK" for x in out]

#os.system("rm -i ./szk")
#os.system("rm -i ./szkb")

os.system("mkcxxO szk.cpp szk")
os.system("mkcxxO szkb.cpp szkb")

while True:
    t = Test()
    print(t.str())
    print(t.get())
    print(t.exp())
    assert t.get() == t.exp()
