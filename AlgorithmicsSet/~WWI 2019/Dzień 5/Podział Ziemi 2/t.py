import os, sys, random, subprocess, tqdm, traceback, math

def call(command, string=""):
    p = subprocess.run(command, input=string.encode('utf-8'), capture_output=True, check=True, timeout=10)
    return p.stdout.decode("utf-8")

T = int(sys.argv[1])

if not os.path.exists("zie") or os.path.getmtime("zie") < os.path.getmtime("zie.cpp"):
    subprocess.run("~/.local/bin/mkcxxO zie.cpp zie", shell=True)
if not os.path.exists("ziej") or os.path.getmtime("ziej") < os.path.getmtime("ziej.cpp"):
    subprocess.run("~/.local/bin/mkcxxO ziej.cpp ziej", shell=True)

def test(N=(1, 10), W=(0, 1)):
    n, m = random.randint(*N), random.randint(*N)
    k = random.randint(0, 4)
    b = random.randint(max(W[0], 1), 5*W[1])
    s = f"{n} {m} {k} {b}\n"
    for y in range(m):
        s += " ".join(str(random.randint(*W)) for _ in range(n)) + "\n"
    return s

for _ in tqdm.tqdm(range(T)):
    s = test()

    try:
        got = call("./zie", s).strip()
        exp = call("./ziej", s).strip()
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
