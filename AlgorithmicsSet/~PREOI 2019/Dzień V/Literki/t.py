import os, random, string

class Test:
    def __init__(self, S, k):
        self.S, self.k = S, k
    def __str__(self):
        return f"{self.S}\n{self.k}"
    def call(self):
        with open("tmp.in", "w") as f: f.write(str(self))
        os.system("lit.exe < tmp.in > tmp.got.out 2> NUL")
        os.system("lit-brute.exe < tmp.in > tmp.exp.out 2> NUL")
        got = open("tmp.got.out", "r").read().strip()
        exp = open("tmp.exp.out", "r").read().strip()
        return got, exp


for t in range(1024):
    a = random.randint(3, 13)
    k = random.randint(1, a)
    n = random.randint(1, 32)
    A = random.sample(string.ascii_lowercase, a)
    S = "".join(random.choice(A) for _ in range(n))
    for i in range(3):
        E = random.sample(list(range(n)), random.randint(1, n))
        St = ""
        for j in range(n):
            St += S[j]
            if j in E:
                St += S[i]
        S = St
        n = len(S)
    T = Test(S, k)
    print(T)
    got, exp = T.call()
    print(T.call())
    assert got == exp

