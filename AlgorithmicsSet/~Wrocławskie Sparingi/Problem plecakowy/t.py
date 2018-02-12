import os, random

n = 500
m = 5

random.seed(1336)

for i in range(100):
    test = [(random.randint(1, 10), random.randint(1, 10)) for _ in range(n)]
    s = "{} {}\n{}".format(n, m, "\n".join("{} {}".format(a, b) for a, b in test))
    with open("temp/temp.in", "w") as file:
        file.write(s)
    os.system("problem-iota.exe < temp/temp.in > temp/temp.got.out")
    os.system("problem-brute.exe < temp/temp.in > temp/temp.exp.out")
    got = open("temp/temp.got.out").read().strip()
    expected = open("temp/temp.exp.out").read().strip()
    correct = got == expected
    print("{} {}".format(i+1, "+" if correct else "!@#"))
    if not correct:
        print("Test:")
        print(s)
        print("Expected: {}".format(expected))
        print("Got: {}".format(got))
        break
