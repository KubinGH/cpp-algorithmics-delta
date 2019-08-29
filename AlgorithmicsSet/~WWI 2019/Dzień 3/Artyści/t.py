import os, sys, random, subprocess, tqdm, traceback, math

def call(command, string=""):
    p = subprocess.run(command, input=string.encode('utf-8'), capture_output=True, check=True, timeout=10)
    return p.stdout.decode("utf-8")

T = int(sys.argv[1])

if not os.path.exists("art") or os.path.getmtime("art") < os.path.getmtime("art.cpp"):
    subprocess.run("~/.local/bin/mkcxxO art.cpp art", shell=True)
if not os.path.exists("artb") or os.path.getmtime("artb") < os.path.getmtime("artb.cpp"):
    subprocess.run("~/.local/bin/mkcxxO artb.cpp artb", shell=True)

def test():
    n = random.randint(1, 100000)

    l = random.randint(1, min(10**9, n*(n+1)//2))
    r = random.randint(1, min(10**9, n*(n+1)//2))

    if r - l > 10**5:
        r = l + 10**5

    if l > r:
        l, r = r, l

    s = f"{n} {l} {r}\n"
    s += " ".join(str(random.randint(1, 1)) for _ in range(n))

    return s

for _ in tqdm.tqdm(range(T)):
    s = test()

    try:
        got = call("./art", s).strip()
        exp = call("./artb", s).strip()
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
