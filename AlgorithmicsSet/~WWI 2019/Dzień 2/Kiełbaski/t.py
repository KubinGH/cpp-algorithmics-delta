import sys, random, subprocess, tqdm

def call(command, string=""):
    p = subprocess.run(command, input=string.encode('utf-8'), capture_output=True, check=True)
    return p.stdout.decode("utf-8")

T = int(sys.argv[1])
M = int(sys.argv[2])

for _ in tqdm.tqdm(range(T)):
    n = random.randint(2, 20)

    rd = lambda: random.randint(0, M)

    Q = [(rd(), rd(), rd()) for _ in range(n)]

    s = f"{n}\n{' '.join(' '.join(str(x) for x in p) for p in Q)}"

    got = call("./kie", s)

    #print(f"`{got}` `{exp}`")

    if not got:
        print("```", s, "```", sep="\n")

    assert got
