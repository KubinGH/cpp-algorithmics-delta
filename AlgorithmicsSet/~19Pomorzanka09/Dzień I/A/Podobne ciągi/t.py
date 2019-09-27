import subprocess, random, os

subprocess.run(['mkcxxO', 'pod.cpp', 'pod'])
subprocess.run(['mkcxxO', 'podb.cpp', 'podb'])

for _ in range(2048):
    print(_, flush=True)
    n, q = random.randint(1, 100), random.randint(1, 100)
    s = f"{n}\n"
    s += " ".join(random.choice("01") for _ in range(n)) + "\n"
    s += f"{q}\n"
    for i in range(q):
        a, b = random.randint(1, n), random.randint(1, n)
        if a > b:
            a, b = b, a
        s += f"{a} {b}\n"

    with open("t.in", "w") as f:
        f.write(s)

    os.system("./pod < t.in > t.got")
    os.system("./podb < t.in > t.exp")

    got = int(open("t.got", "r").read().strip())
    exp = int(open("t.exp", "r").read().strip())

    print(got, exp)

    assert got == exp
