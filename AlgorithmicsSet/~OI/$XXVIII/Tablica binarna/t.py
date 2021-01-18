import os, subprocess, random, time, tqdm

code = "tab"

def call_with_io(command, string, shell=False):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=shell
    ).stdout.decode()

os.system(f"rm {code} {code}b")
os.system(f"mkcxxO {code}.cpp {code}")
os.system(f"mkcxxO {code}b.cpp {code}b")

class Test:
    def __init__(self, n, m, Q):
        self.n, self.m, self.Q = n, m, Q

    @classmethod
    def random(cls):
        q = random.randint(0, 7)**2 + random.randint(1, 20)
        if random.randint(0, 5):
            n, m = random.randint(1, 4), random.randint(1, 4)
        elif random.randint(0, 2):
            n, m = random.randint(1, 3), random.randint(1, 5)
        else:
            n, m = random.randint(1, 2), random.randint(1, 7)
        if random.randint(0, 1):
            n, m = m, n
        Q = []
        for _ in range(q):
            x1, y1, x2, y2 = random.randint(1, n), random.randint(1, m), \
                             random.randint(1, n), random.randint(1, m)
            if x1 > x2: x1, x2 = x2, x1
            if y1 > y2: y1, y2 = y2, y1
            Q.append((x1, y1, x2, y2))
        return cls(n, m, Q)

    def str(self):
        return f"{self.n} {self.m} {len(self.Q)}\n" + \
               "\n".join(" ".join(str(x) for x in row) for row in self.Q)

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
