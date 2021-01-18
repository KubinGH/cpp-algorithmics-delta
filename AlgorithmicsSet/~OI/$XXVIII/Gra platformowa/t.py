import os, subprocess, random, time, tqdm

code = "gra"

def call_with_io(command, string, shell=False):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=shell
    ).stdout.decode()

os.system(f"rm {code} {code}b")
os.system(f"mkcxxO {code}.cpp {code}")
os.system(f"mkcxxO {code}b.cpp {code}b")

class Test:
    def __init__(self, x, H, Q):
        self.x, self.H, self.Q = x, H, Q

    @classmethod
    def random(cls):
        if random.randint(0, 3):
            n, x, q = random.randint(1, 20), random.randint(1, 50), random.randint(1, 25)
        else:
            n, x, q = random.randint(1, 3), random.randint(1, 10), random.randint(1, 3)
        p = random.uniform(0, 1)
        H = [[]]
        for y in range(n):
            H.append([])
            last = False
            for i in range(2, x):
                if not last and i not in H[-2] and random.uniform(0, 1) <= p:
                    H[-1].append(i)
                    last = True
                else:
                    last = False
        H.pop(0)
        Q = [random.randint(1, n) for _ in range(q)]
        return cls(x, H, Q)

    def str(self):
        return f"{len(self.H)} {self.x} {len(self.Q)}\n" + \
                "\n".join(" ".join([str(len(row))] + [str(x) for x in row]) for row in self.H) + "\n" + \
                "\n".join(str(x) for x in self.Q)

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
