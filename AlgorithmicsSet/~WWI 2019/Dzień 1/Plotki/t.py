import sys, random, subprocess, tqdm

def call(command, string=""):
    return subprocess.run(command, input=string.encode('utf-8'), capture_output=True).stdout.decode("utf-8")

T = int(sys.argv[1])

for _ in tqdm.tqdm(range(T)):
    n = random.randint(2, 1000)
    A, B, C = [list(range(n)) for _ in range(3)]
    random.shuffle(A)
    random.shuffle(B)
    random.shuffle(C)

    s = f"{n}\n{' '.join(str(x) for x in A)}\n{' '.join(str(x) for x in B)}\n{' '.join(str(x) for x in C)}"

    got = call("./plo", s).split(";")[-1]
    exp = call("./plob", s).split(";")[-1]

    #print(f"`{got}` `{exp}`")

    if got != exp:
        print("```", s, "```", sep="\n")

    assert got == exp
