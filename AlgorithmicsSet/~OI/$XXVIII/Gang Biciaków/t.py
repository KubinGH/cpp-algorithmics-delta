import os, subprocess, random, time, tqdm, math

code = "gan"

def call_with_io(command, string, shell=False):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=shell
    ).stdout.decode()

os.system(f"rm {code} {code}b")
os.system(f"mkcxxO {code}.cpp {code}")
os.system(f"mkcxxO {code}b.cpp {code}b")

class Test:
    def __init__(self, m, E, Q):
        self.m, self.E, self.Q = m, E, Q

    @classmethod
    def random(cls):
        if random.randint(0, 5):
            n, q = random.randint(2, 10**2), random.randint(1, 10**2)
        elif random.randint(0, 3):
            n, q = random.randint(2, 10**1), random.randint(1, 10**3)
        elif random.randint(0, 2):
            n, q = random.randint(2, 10**3), random.randint(1, 10**1)
        else:
            n, q = random.randint(2, 20), random.randint(1, 10)

        if random.randint(0, 3):
            m = random.randint(1, 2*n)
        elif random.randint(0, 1):
            m = random.randint(1, max(3, int(n**0.5)))
        else:
            m = random.randint(1, 16)

        k, l = random.randint(0, 4)**2, random.randint(0, 5)**2
        mn = random.randint(0, 5)

        if random.randint(0, 1):
            a, b = 0, 1
        elif random.randint(0, 1):
            a, b = 0.4, 0.6
        elif random.randint(0, 1):
            a, b = 0.9, 1
        elif random.randint(0, 1):
            a, b = 0, 0
        else:
            a, b = 1, 1

        E = []
        for i in range(1, n):
            E.append([
                random.randint(math.floor((i-1)*a), math.ceil((i-1)*b)), i,
                random.randint(1, m) if mn else 1
            ])

        renum = list(range(1, n+1))
        if random.randint(0, 1):
            random.shuffle(renum)
        elif random.randint(0, 1):
            renum.reverse()
        for i in range(n - 1):
            for t in range(2):
               E[i][t] = renum[E[i][t]]
            if random.randint(0, 1):
                E[i][0], E[i][1] = E[i][1], E[i][0]
            E[i] = tuple(E[i])
        random.shuffle(E)

        Q = []
        for i in range(q):
            if random.randint(0, k) < random.randint(0, l):
                Q.append(('Z', random.randint(1, n)))
            else:
                Q.append(('B', random.randint(1, n - 1), random.randint(1, m)))

        return cls(m, E, Q)

    def str(self):
        return f"{len(self.E)+1} {self.m} {len(self.Q)}\n" + \
               "\n".join(" ".join(str(x) for x in row) for row in self.E) + "\n" + \
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
