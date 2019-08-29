import os, sys, random, subprocess, tqdm, traceback, math

def call(command, string=""):
    p = subprocess.run(command, input=string.encode('utf-8'), capture_output=True, check=True)
    return p.stdout.decode("utf-8")

T = int(sys.argv[1])

if not os.path.exists("rbt") or os.path.getmtime("rbt") < os.path.getmtime("rbt.cpp"):
    subprocess.run("~/.local/bin/mkcxxO rbt.cpp rbt", shell=True)
if not os.path.exists("rbtb") or os.path.getmtime("rbtb") < os.path.getmtime("rbtb.cpp"):
    subprocess.run("~/.local/bin/mkcxxO rbtb.cpp rbtb", shell=True)

α = 0
β = 1
assert α <= β

def test():
    n = random.randint(1, 1000)
    E = []
    for i in range(1, n):
        E.append((random.randint(math.floor(α*(i-1)), math.ceil(β*(i-1))), i))
        if random.randint(0, 1) == 1:
            E[-1] = (E[-1][1], E[-1][0]);
    random.shuffle(E)

    q = random.randint(1, 1000)

    s = f"{n} {q}\n"
    s += " ".join(random.choice("01") for _ in range(n)) + "\n"
    for u, v in E:
        s += f"{u+1} {v+1}\n"
    for _ in range(q):
        s += f"{random.randint(1, 2)} {random.randint(1, n)}\n"

    return s

for _ in tqdm.tqdm(range(T)):
    s = test()

    try:
        got = call("./rbt", s).strip()
        exp = call("./rbtb", s).strip()
        #exp = got
    except subprocess.CalledProcessError:
        got = float('nan')
        exp = float('nan')
        traceback.print_exc()

    if not (got == exp):
        print(f"{repr(got)} {repr(exp)}")
        print(s)
        with open(f"failed{random.randint(0, 2**16 - 1)}.in", "w") as f:
            f.write(s)

    assert got == exp
