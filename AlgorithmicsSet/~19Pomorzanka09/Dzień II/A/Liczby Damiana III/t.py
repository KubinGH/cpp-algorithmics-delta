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
    T = random.randint(1, 30)
    s = f"{T}\n"
    for i in range(T):
        a, b, c = random.randint(2, 30), random.randint(2, 30), random.randint(2, 30)
        s += f"{a}^{b}^{c}\n"
    with open("t.in", "w") as f:
        f.write(s)

    got = call("./pot", s).split(";")[-1].strip()
    exp = call("./potb", s).split(";")[-1].strip()

    if got != exp:
        print(f"`{got}` `{exp}`")
        print("```", s, "```", sep="\n")

    assert got == exp
