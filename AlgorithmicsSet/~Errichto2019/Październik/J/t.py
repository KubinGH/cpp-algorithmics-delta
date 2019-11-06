import random, subprocess

def call_with_io(command, string):
    return subprocess.run(
        command, input=string.encode(), capture_output=True,
        timeout=5
    ).stdout.decode()

def sim(x, n, k, a, b, c, d, st):
    assert 1 <= x <= k
    p = q = 0
    while x <= n:
        if st == 0:
            if a <= x <= b:
                q += 1
            else:
                p += 1
        else:
            if c <= x <= d:
                p += 1
            else:
                q += 1
        st ^= 1
        x += k
    return p == q

subprocess.run(f"mkcxx j.cpp j", shell=True)
for t in range(1024):
    while True:
        n = random.randint(1, 30)
        a, b, c, d = sorted([random.randint(1, n) for _ in range(4)])
        if b == c:
            continue
        if random.randint(0, 1):
            a, b, c, d = c, d, a, b
        k = random.randint(1, n)
        break

    got = call_with_io("./j", f"{n} {k}\n{a} {b} {c} {d}").strip().replace('\n', ' ')
    print(f"n={n} k={k} {a}..{b} {c}..{d} -> `{got}`")
    if got == "-1":
        for st in (0, 1):
            for x in range(1, k+1):
                ss = sim(x, n, k, a, b, c, d, st)
                if ss:
                    print("?!", x, st)
                assert not ss
    else:
        sp = got.split()
        x = int(sp[0])
        assert sp[1] in ("Dima", "Mitya")
        st = sp[1] == "Mitya"
        assert sim(x, n, k, a, b, c, d, st)
