import os, random

class Test:
    def __init__(self, n, C):
        self.n, self.C = n, C
    @classmethod
    def random(cls, n, B=(1, 10**9)):
        return cls(n, [[random.randint(*B) for _ in range(n)] for _ in range(n)])
    def __str__(self):
        rows = [" ".join(str(x) for x in row) for row in self.C]
        sC = "\n".join(rows)
        return f"{self.n}\n{sC}"

def median(seq):
    if len(seq) % 2:
        return seq[len(seq)//2]
    else:
        return (seq[len(seq)//2] + seq[len(seq)//2+1]) / 2

def brute(T):
    n, C = T.n, T.C
    def call(x, y, seq=[]):
        seq.append(C[x][y])
        if x == n-1 and y == n-1:
            seq.sort()
            return median(seq)
        elif x == n-1:
            return call(x, y+1, seq.copy())
        elif y == n-1:
            return call(x+1, y, seq.copy())
        else:
            return max(
                call(x+1, y, seq.copy()),
                call(x, y+1, seq.copy())
            )
    return call(0, 0)

def model(T):
    with open("tmp.in", "w") as f: f.write(str(T))
    os.system("amm.exe < tmp.in > tmp.out 2> NUL")
    return int(open("tmp.out", "r").read().strip())

n = 5

for t in range(128):
    print(t)
    T = Test.random(n, (1, n**2))
    got, exp = model(T), brute(T)
    if got != exp:
        print("!@#")
        print(T)
        print(f"? {got}")
        print(f"> {exp}")
    
        z = random.randint(0, 2**16-1)
        print(z)
        with open(f"failed{z}.in", "w") as f: 
            f.write(str(T))
            f.write("\n###\n? {got}\n> {exp}")
