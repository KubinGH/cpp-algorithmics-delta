import os, sys, random, subprocess, tqdm, traceback

def call(command, string=""):
    p = subprocess.run(command, input=string.encode('utf-8'), capture_output=True, check=True)
    return p.stdout.decode("utf-8")

T = int(sys.argv[1])

if not os.path.exists("uty0") or os.path.getmtime("uty0") < os.path.getmtime("uty0.cpp"):
    subprocess.run("~/.local/bin/mkcxxO uty0.cpp uty0", shell=True)
if not os.path.exists("utyb") or os.path.getmtime("utyb") < os.path.getmtime("utyb.cpp"):
    subprocess.run("~/.local/bin/mkcxxO utyb.cpp utyb", shell=True)

def test():
    n = random.randint(2, 5)
    E = []
    for i in range(1, n):
        E.append((random.randint(0, i - 1), i, random.randint(-5, 5)))
        if random.randint(0, 1) == 1:
            E[-1] = (E[-1][1], E[-1][0], E[-1][2]);
    random.shuffle(E)

    k = random.randint(1, n - 1)
    s = f"{n} {k}\n"
    for u, v, w in E:
        s += f"{u+1} {v+1} {w}\n"

    return s

for _ in tqdm.tqdm(range(T)):
    s = test()

    try:
        got = call("./uty0", s).strip()
        exp = call("./utyb", s).strip()
    except subprocess.CalledProcessError:
        got = float('nan')
        exp = float('nan')
        traceback.print_exc()

    if not (got == exp):
        print(f"{repr(got)} {repr(exp)}")
        print(s)

    assert got == exp
