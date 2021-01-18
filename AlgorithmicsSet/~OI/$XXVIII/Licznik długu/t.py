import os, subprocess, random, time, tqdm

code = "lic"

def call_with_io(command, string, shell=False):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=shell
    ).stdout.decode()

os.system(f"rm {code}")
os.system(f"mkcxxO {code}.cpp {code}")

class Test:
    def __init__(self, n, A, B, Q):
        self.n, self.A, self.B, self.Q = n, A, B, Q

    @classmethod
    def random(cls):
        n, q = random.randint(2, 20), random.randint(1, 5)
        get_digit = (lambda: random.randint(0, 9)) if random.randint(0, 4) else (lambda: 5*random.randint(0, 1))
        A, B = [[get_digit() for _ in range(n-1)] for _ in range(2)]
        Q = []
        for _ in range(q):
            if random.randint(0, 5):
                if random.randint(0, 1):
                    Q.append(('W', random.randint(1, n-1), get_digit()))
                else:
                    Q.append(('Z', random.randint(1, n-1), get_digit()))
            else:
                if random.randint(0, 2):
                    Q.append(('s',))
                else:
                    Q.append(('S', random.randint(1, n)))
        return cls(n, ''.join(str(x) for x in A), ''.join(str(x) for x in B), Q)

    def str(self):
        return f"{self.n} {len(self.Q)}\n{self.A}\n{self.B}\n" + \
                "\n".join(" ".join(str(x) for x in row) for row in self.Q)

    def get(self):
        return call_with_io(f"./{code}", self.str()).strip()

    def exp(self):
        return call_with_io(f"./{code}b", self.str()).strip()

for i in tqdm.tqdm(range(10**4)):
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
