import sys, random, subprocess, tqdm

def call(command, string=""):
    return subprocess.run(command, input=string.encode('utf-8'), capture_output=True).stdout.decode("utf-8")

T = int(sys.argv[1])

for k in range(1, 4):
    print(f"k = {k}")
    for _ in tqdm.tqdm(range(T)):
        w, h = random.randint(k, 50), random.randint(k, 50)
        A = [[random.randint(-100, 100) for _ in range(w)] for _ in range(h)]
        s = f"{w} {h} {k}\n"
        s += "\n".join(" ".join(str(x) for x in row) for row in A)

        #print(f"[{w} x {h}]")
        got = call("./zam", s).split(";")[-1]
        exp = call("./zam7", s).split(";")[-1]

        #print(f"`{got}` `{exp}`")

        if got != exp:
            print("```", s, "```", sep="\n")

        assert got == exp
