import os, sys, random, subprocess, tqdm, time, cho

def call(command, string=""):
    p = subprocess.run(command, input=string.encode('utf-8'), capture_output=True, check=True)
    return p.stdout.decode("utf-8")

def red(o):
    return [l.rstrip() for l in o.rstrip().split("\n")]

while True:
    if not os.path.exists("choinka") or os.path.getmtime("choinka") < os.path.getmtime("choinka.c"):
        subprocess.run("gcc choinka.c -o choinka", shell=True)
    for n in tqdm.tqdm(range(2, 102)):
        s = f"{n}\n"

        got = red(call("./choinka", s))
        exp = red(cho.main(n))

        if got != exp:
            print("Oh no! WA")
            print(s)
            print(f'Got {repr(got)} != {repr(exp)}')
            time.sleep(2)
            break

        assert got == exp

    time.sleep(1.5)
