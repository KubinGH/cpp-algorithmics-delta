import sys, random, subprocess, tqdm

def call(command, string=""):
    return subprocess.run(command, input=string.encode('utf-8'), capture_output=True).stdout.decode("utf-8")

def slst(a):
    return " ".join(str(x) for x in a)

T = int(sys.argv[1])

for _ in tqdm.tqdm(range(T)):
    n = random.randint(2, 1000)
    m = random.randint(2, n)
    P = list(range(1, m+1))
    random.shuffle(P)

    q = random.randint(1, 1000)

    s = f"{n} {m} {q}\n{slst(P)}\n"
    for i in range(q):
        s += f"{random.randint(1, n)}\n"

    got = [int(l.strip()) for l in call("./wys", s).split()]
    exp = [int(l.strip()) for l in call("./wysb", s).split()]


    if got != exp:
        print(f"`{got}` `{exp}`")
        print("```", s, "```", sep="\n")

    assert got == exp
