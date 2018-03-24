import os, random

t = 200
n = 7
bounds = (1, 100)

for i in range(t):
    test = [random.randint(*bounds) for _ in range(n)]
    with open("temp/tmp.in", "w") as file:
        file.write("{} {}\n{}".format(n, random.randint(max(test), bounds[1]), "\n".join(str(x) for x in test)))
    print(test)
    os.system("cows_nexp < temp/tmp.in > temp/tmp.exp.out")
    os.system("cows_2exp < temp/tmp.in > temp/tmp.got.out")
    with open("temp/tmp.com.in", "w") as file:
        file.write("\n".join((open("temp/tmp.in").read(), open("temp/tmp.got.out").read())))
    os.system("cows_verify < temp/tmp.com.in > temp/tmp.ver.out")
    exp = open("temp/tmp.exp.out").read().strip().split()[0]
    got = open("temp/tmp.got.out").read().strip().split()[0]
    ver = open("temp/tmp.ver.out").read().strip() == "+"
    print(ver, got, exp)
    if ver and got == exp:
        print("+")
    else:
        print("!@#")
        break
