import os, subprocess, random, time, tqdm

code = "cuk"

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
    def random(cls, N=15, A=7):
        n = random.randint(3, 10)
        if random.randint(0, 24):
            return cls([[random.randint(0, A) for _ in range(3)] for _ in range(n)])
        elif random.randint(0, 3):
            i = random.randint(0, 2)
            return cls([[random.randint(0, A) if i!=k else 0 for k in range(3)] for _ in range(n)])
        else:
            i = random.randint(0, 2)
            return cls([[random.randint(0, A) if i==k else 0 for k in range(3)] for _ in range(n)])

    def str(self):
        return f"{len(self.A)}\n" + "\n".join(" ".join(str(x) for x in row) for row in self.A)

    def get(self):
        return call_with_io(f"./{code}", self.str()).strip()

    def exp(self):
        return call_with_io(f"./{code}b", self.str()).strip()

for i in tqdm.tqdm(range(10**5)):
    t = Test.random()
    a, b = t.get(), t.exp()
    if a != b:
        print('- * -')
        print(t.str())
        print('- ! -')
        print(a)
        print('- ? -')
        print(b)
        with open(f"failed{int(time.time())}.in", "w") as f:
            f.write(t.str())
        print("!@#")
        break
