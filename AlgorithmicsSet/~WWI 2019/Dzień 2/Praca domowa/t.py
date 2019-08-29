import os, sys, random, subprocess, tqdm, time

def call(command, string=""):
    p = subprocess.run(command, input=string.encode('utf-8'), capture_output=True, check=True)
    return p.stdout.decode("utf-8")

T = int(sys.argv[1])

while True:
    if os.path.getmtime("pra") < os.path.getmtime("pra.cpp"):
        subprocess.run("~/.local/bin/mkcxxO pra.cpp pra", shell=True)
    if os.path.getmtime("pra0") < os.path.getmtime("pra0.cpp"):
        subprocess.run("~/.local/bin/mkcxxO pra0.cpp pra0", shell=True)
    for i in tqdm.tqdm(range(T)):
        n, k = random.randint(1, i*10 + 10), random.randint(1, i*10 + 10)

        s = f"{n} {k}"

        got = call("./pra", s)
        exp = call("./pra0", s)

        if got != exp:
            print("Oh no! WA")
            print(s)
            print(f'Got `{got}` != `{exp}`')
            time.sleep(2)
            break

        assert got == exp

    time.sleep(1.5)
