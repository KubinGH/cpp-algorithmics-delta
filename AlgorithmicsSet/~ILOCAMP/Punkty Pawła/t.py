import itertools, random, os

def X(a, b):
    return a[0]*b[1] - a[1]*b[0];

def test(n, B=(0, 24)):
    while True:
        T = [(random.randint(*B), random.randint(*B)) for _ in range(n)]
        ok = True
        for i in range(n):
            for j in range(i+1, n):
                for k in range(j+1, n):
                    if X((T[j][0]-T[i][0], T[j][1]-T[i][1]), 
                         (T[k][0]-T[i][0], T[k][1]-T[i][1])) == 0:
                        ok = False; break
                if not ok: break
            if not ok: break
        if ok: break
    return n, random.randint(3, n), T

def getput(n, k, T):
    nl = '\n'
    return f"{n} {k}{nl}{f'{nl}'.join(f'{x[0]} {x[1]}' for x in T)}"

def call(n, k, T, p="paw.exe"):
    with open("tmp.in", "w") as f: f.write(getput(n, k, T))
    os.system(f"{p} < tmp.in > tmp.out 2> NUL")
    out = open("tmp.out", "r").read().strip()
    return float(out)

for i in range(64):
    print(i)
    n, k, T = test(12, (0, 7))

    got = call(n, k, T, "paw.exe")
    exp = call(n, k, T, "paw-asia.exe")
    print(got, exp)
    if got != exp:    
        print(f"{i}: {n} {k} {T}")
        print("?", got)
        print(">", exp)
        tn = f"faulty{random.randint(0, 2**16-1)}.in"
        print("!@#$", tn)
        with open(tn, "w") as f: 
            f.write(getput(n, k, T))
            f.write(f"\n###\n? {got}\n> {exp}")
