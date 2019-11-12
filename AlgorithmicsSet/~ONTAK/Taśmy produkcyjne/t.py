import subprocess, random

def call_with_io(command, string):
    return subprocess.run(
        command, input=string.encode(), capture_output=True,
        shell=True, timeout=5
    ).stdout.decode()

for t in range(1024):
    print(t)
    n, m = random.randint(2, 1000), random.randint(2, 1000)
    mach = []
    for i in range(m):
        a, b = [random.randint(1, n) for _ in range(2)]
        while a == b:
            a, b = [random.randint(1, n) for _ in range(2)]
        mach.append((a, b))
    q = random.randint(2, 1000)
    que = []
    for i in range(q):
        c = random.choice("CQ")
        if c == "C":
            que.append((c, random.randint(1, m)))
        elif c == "Q":
            que.append((c, random.randint(1, n)))
    test = f"{n} {m}\n" + "\n".join(f"{a} {b}" for a, b in mach) + f"\n{q}\n" + "\n".join(f"{c} {k}" for c, k in que)
    got = call_with_io("./tpr", test)
    exp = call_with_io("./tprb", test)
    if got != exp:
        print(test)
        break
