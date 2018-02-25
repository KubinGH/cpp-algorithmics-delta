import subprocess, random

tests = 10000

random.seed(1337)

for i in range(1, tests+1):
    test = random.randint(1, 2**200)
    s = bin(test)[2:]
    with open("temp/temp.in", "w") as file:
        file.write(s)
    subprocess.run("hex.exe < temp/temp.in > temp/temp.got.out", shell=True)
    expected = hex(test)[2:].upper()
    got = open("temp/temp.got.out", "r").read().strip()
    correct = got == expected
    if correct:
        print("{} OK ({} == {})".format(i, got, expected))
    else:
        print("{} WA ({} != {})".format(i, got, expected))
        print(s)
        break
