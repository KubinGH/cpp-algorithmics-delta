import random, os

def generate(N=(1, 10**5), Q=(1, 10**2), B=(1, 10**9)):
    n, q = random.randint(*N), random.randint(*Q)
    S = set()
    while len(S) < n:
        S.add(random.randint(*B))
    A = list(S)
    random.shuffle(A)
    P = [sorted((random.randint(1, n), random.randint(1, n))) for _ in range(q)]
    out = f"{n} {q}\n"
    out += " ".join(str(x) for x in A); out += "\n"
    out += "\n".join(f"{a} {b}" for a, b in P);
    return out

for _ in range(128):
    test = generate()
    with open("tmp.in", "w") as f: f.write(test)
    code = os.system("ran.exe < tmp.in > tmp.out")
    print(code)
    if code != 0:
        print("!@#")
        with open("faulty.in", "w") as f: f.write(test)
        break
