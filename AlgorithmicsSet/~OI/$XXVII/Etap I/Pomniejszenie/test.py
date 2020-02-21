import subprocess, random, string

def call_with_io(command, string):
    return subprocess.run(
        command, input=string.encode(), capture_output=True,
        timeout=5
    ).stdout.decode()

st = input("first -> ")
nd = input("second -> ")

subprocess.run(f"mkcxxO {st}.cpp {st}", shell=True)
subprocess.run(f"mkcxxO {nd}.cpp {nd}", shell=True)

n = int(input("n = "))

def rnd():
    return ''.join(random.choice(string.digits) for _ in range(n))

for t in range(2**16):
    A, B = rnd(), rnd()
    if A < B:
        A, B = B, A
    k = random.randint(1, n)

    test = f"1\n{A} {B} {k}"

    out1 = call_with_io(f"./{st}", test).strip()
    out2 = call_with_io(f"./{nd}", test).strip()

    print(f"{t: 5}. {A} {B} {k} -> {out1} ? {out2}", flush=True)

    assert out1 == out2
