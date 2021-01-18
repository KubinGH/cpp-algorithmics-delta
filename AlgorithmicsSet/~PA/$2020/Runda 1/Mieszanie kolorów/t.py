import os, subprocess, random, time, tqdm

code = "kol"

def call_with_io(command, string, shell=False):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=shell
    ).stdout.decode()

# os.system(f"rm {code} {code}b")
os.system(f"mkcxxO {code}.cpp {code}")
os.system(f"mkcxxO {code}b.cpp {code}b")

class Test:
    def __init__(self, n, Q):
        self.n, self.Q = n, Q

    @classmethod
    def random(cls):
        n, m = random.randint(1, 7), random.randint(1, 7)
        Q = []
        for i in range(m):
            a, b = random.randint(1, n), random.randint(1, n)
            if a > b:
                a, b = b, a
            Q.append((a, b, random.randint(1, 3)))
        return cls(n, Q)

    def str(self):
        return f"{self.n} {len(self.Q)}\n" + "\n".join(" ".join(str(x) for x in q) for q in self.Q)

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
        os.system("mkdir fail")
        with open(f"fail/failed{int(time.time())}.in", "w") as f:
            f.write(t.str())
        print("!@#")
        break
