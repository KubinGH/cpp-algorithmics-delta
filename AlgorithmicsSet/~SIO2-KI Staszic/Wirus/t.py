import os, random

k = 10
m = 4

for i in range(200):
    print("{}: ".format(i))
    test = [tuple(random.sample(range(1, m+1), 2)) for _ in range(k)]
    with open("temp/tmp.in", "w") as file:
        file.write("{}\n{}".format(k, "\n".join("{} {}".format(*p) for p in test)))
    os.system("wirus-lambda.exe < temp/tmp.in > temp/tmp.got.out")
    os.system("wirus-brute.exe < temp/tmp.in > temp/tmp.exp.out")
    got = open("temp/tmp.got.out", "r").read().strip()
    expected = open("temp/tmp.exp.out", "r").read().strip()
    print(test)
    print(" ".join(got.split()[1:]))
    print([line.strip() for line in expected.split("\n")[1:]])
    is_correct = (got == expected == "NIE") or \
                 (" ".join(got.split()[1:]) in [line.strip() for line in expected.split("\n")[1:]])
    if not is_correct:
        print("!@#")
        break
    print()
