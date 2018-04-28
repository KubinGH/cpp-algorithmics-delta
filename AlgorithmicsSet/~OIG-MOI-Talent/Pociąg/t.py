import os, random

n = 20

random.seed(1337)

for i in range(100):
    test = [list(range(1, n+1)), list(range(1, n+1))]
    random.shuffle(test[0]), random.shuffle(test[1])
    s = "{}\n{}\n{}".format(n, " ".join(str(x) for x in test[0]), " ".join(str(x) for x in test[1]))
    with open("temp/temp.in", "w") as file:
        file.write(s)
    os.system("pociag.exe < temp/temp.in > temp/temp.got.out")
    os.system("pociag_brute.exe < temp/temp.in > temp/temp.exp.out")
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
