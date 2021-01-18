import os, subprocess, random, time, tqdm

code = "min"

def call_with_io(command, string, shell=False):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=shell
    ).stdout.decode()

os.system(f"rm {code} {code}b")
os.system(f"mkcxxO {code}.cpp {code}")
os.system(f"mkcxxO {code}b.cpp {code}b")

class Test:
    def __init__(self, A, R):
        self.A, self.R = A, R
        assert len(self.A) == len(self.R)

    @classmethod
    def random(cls):
        if random.randint(0, 3):
            A = random.sample(list(range(15)), random.randint(1, 12))
        elif random.randint(0, 3):
            A = random.sample(list(range(60)), random.randint(1, 12))
        else:
            A = random.sample(list(range(10**4)), random.randint(1, 12))
        n = len(A)
        A.sort()
        if random.randint(0, 3):
            R = [random.randint(0, 4)**2 + random.randint(0, 5) for _ in range(n)]
        elif random.randint(0, 1):
            R = [random.randint(0, 15)**2 + random.randint(0, 20) for _ in range(n)]
        else:
            R = [random.randint(0, 5) for _ in range(n)]
        return cls(A, R)

    def str(self):
        return f"{len(self.A)}\n" + "\n".join(f"{a} {r}" for a, r in zip(self.A, self.R))

    def get(self):
        return call_with_io(f"./{code}", self.str()).strip()

    def exp(self):
        return call_with_io(f"./{code}b", self.str()).strip()

# bar = lambda obj: obj
bar = tqdm.tqdm

for i in bar(range(10**6)):
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
