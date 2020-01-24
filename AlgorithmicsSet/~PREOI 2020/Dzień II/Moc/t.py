import subprocess
import random
import functools, operator

mod = 10**9 + 7

def mmul(a, b):
    return (a * b) % mod

def product(it):
    return functools.reduce(mmul, it, 1)

def call_with_io(command, string=""):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=True
    ).stdout.decode()

class Test:
    def __init__(self):
        n = random.randint(1, 200)
        self.k = random.randint(0, 10)
        self.A = [random.randint(1, 6) for _ in range(n)]

    def __str__(self):
        return "{} {}\n{}".format(len(self.A), self.k, " ".join(str(x) for x in self.A))

    def get(self):
        return int(call_with_io("./moc", str(self)).strip())

    def exp(self):
        n = len(self.A)
        r = 0
        for i in range(n):
            for j in range(i+1, n+1):
                if sum(self.A[i:j]) > self.k:
                    r += product(self.A[i:j])
        return r % mod

print(call_with_io("rm -i ./moc"))
print(call_with_io("mkcxxO moc.cpp moc"))

for _ in range(1000):
    t = Test()
    print(t)
    print(f"got {t.get()}, exp {t.exp()}")
    assert t.get() == t.exp()
