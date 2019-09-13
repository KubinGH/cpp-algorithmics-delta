import random, subprocess, time, itertools

def call(command, string=""):
    start = time.time()
    p = subprocess.run(command, input=string.encode('utf-8'), capture_output=True, check=True, timeout=10)
    finish = time.time()
    return p.stdout.decode("utf-8")

def powerset(S):
    return itertools.chain.from_iterable(itertools.combinations(S, r) for r in range(len(S)+1))

subprocess.run("mkcxx arithmetic-mean-real.cpp ari", shell=True)

for _ in range(2048):
    n = random.randint(1, 20)
    a = random.randint(0, 15)
    w = [random.randint(0, 15) for i in range(n)]

    exists = None
    if n < 20:
        for p in powerset(w):
            if (a == 0 or p) and sum(p) == len(p) * a:
                exists = True
                break
        else:
            exists = False

    print(n, a, w, exists, flush=True)

    s = f"{n} {a}\n{' '.join(str(x) for x in w)}\n"
    with open("t.in", "w") as f:
        f.write(s)
    out = call("./ari", s).split('\n')

    print("->", out, flush=True)

    if out[0] == "NIE":
        assert exists is None or not exists
        print(flush=True)
        continue

    no = [int(i) for i in out[2].split()]
    print(" #", no)

    assert len(no) == int(out[1])

    assert sum(no) == len(no) * a

    print(flush=True)
