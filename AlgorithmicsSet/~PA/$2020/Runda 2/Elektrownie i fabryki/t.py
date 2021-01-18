import os, subprocess, random, time, tqdm

code = "ele"

def call_with_io(command, string, shell=False):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=shell
    ).stdout.decode()

os.system(f"rm {code} {code}b")
os.system(f"mkcxxO {code}.cpp {code}")
os.system(f"mkcxxO {code}b.cpp {code}b")

class Test:
    def __init__(self, A):
        self.A = A

    @classmethod
    def random(cls):
        n = random.randint(1, 10)**2 + random.randint(0, 5)
        x = random.choice((1, 10, 10**5, 10**9))
        p = random.randint(0, 5)
        return cls([random.randint(-x, x) * (not random.randint(0, p)) for _ in range(n)])

    def str(self):
        return f"{len(self.A)}\n" + " ".join(str(a) for a in self.A)

    def get(self):
        return call_with_io(f"./{code}", self.str()).strip()

    def exp(self):
        return call_with_io(f"./{code}b", self.str()).strip()

for i in tqdm.tqdm(range(5 * 10**4)):
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
