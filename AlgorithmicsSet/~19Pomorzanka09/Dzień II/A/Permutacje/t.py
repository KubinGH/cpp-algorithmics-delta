import sys, random, subprocess, time

def call(command, string=""):
    start = time.time()
    out = subprocess.run(command, input=string.encode('utf-8'), capture_output=True).stdout.decode("utf-8")
    end = time.time()
    print(f"`{command}` done in {end - start:.3f}s")
    return out

T = int(sys.argv[1])

for _ in range(T):
    print(_, flush=True)
    n = random.randint(2, 6)
    A, B, C = [list(range(1, n+1)) for _ in range(3)]
    random.shuffle(A)
    random.shuffle(B)
    random.shuffle(C)

    s = f"{n}\n{' '.join(str(x) for x in A)}\n{' '.join(str(x) for x in B)}\n{' '.join(str(x) for x in C)}"
    with open("t.in", "w") as f:
        f.write(s)

    got = call("./plo", s).split(";")[-1].strip()
    exp = call("./per", s).split(";")[-1].strip()


    if got != exp:
        print(f"`{got}` `{exp}`")
        print("```", s, "```", sep="\n")

    assert got == exp
