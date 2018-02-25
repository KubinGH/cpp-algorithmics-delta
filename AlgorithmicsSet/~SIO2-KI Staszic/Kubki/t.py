import subprocess, random

tests = 100

n = 200
random.seed(1337+3)

for i in range(1, tests+1):
    test = list(range(1, n+1))
    random.shuffle(test)
    s = "{}\n{}".format(n, " ".join(str(x) for x in test))
    with open("temp/temp.in", "w") as file:
        file.write(s)
    subprocess.run("kubki.exe < temp/temp.in > temp/temp.got.out", shell=True)
    if n < 10**5:
        subprocess.run("kubki_brute.exe < temp/temp.in > temp/temp.exp.out", shell=True)
    got = open("temp/temp.got.out", "r").read().strip()
    expected = open("temp/temp.exp.out", "r").read().strip()
    correct = got == expected
    if correct:
        print("{} OK ({} == {})".format(i, got, expected))
    else:
        print("{} WA ({} != {})".format(i, got, expected))
        if n < 100:
            print(s)
        break
