import os, subprocess, random, time, tqdm
from sympy import isprime

code = "mal"

def call_with_io(command, string, shell=False):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=shell
    ).stdout.decode()

os.system(f"rm {code} {code}b")
os.system(f"mkcxxO {code}.cpp {code}")
os.system(f"mkcxxO {code}0.cpp {code}b")

class Test:
    def __init__(self, n, m, p):
        self.n, self.m, self.p = n, m, p

    @classmethod
    def random(cls):
        while not isprime(p := random.randint(10**8, 10**9)):
            pass
        return cls(random.randint(1, 50), random.randint(1, 9), p)

    def str(self):
        return f"{self.n} {self.m} {self.p}"

    def get(self):
        return call_with_io(f"./{code}", self.str()).strip()

    def exp(self):
        return call_with_io(f"./{code}b", self.str()).strip()

# bar = lambda obj: obj
bar = tqdm.tqdm

for i in bar(range(10**4)):
    t = Test.random()
    a, b = t.get(), t.exp()
    if a != b:
        print('- * -')
        print(t.str())
        print('- ! -')
        print(a)
        print('- ? -')
        print(b)
        os.system("mkdir fail")
        with open(f"fail/failed{int(time.time())}.in", "w") as f:
            f.write(t.str())
        print("!@#")
        break
