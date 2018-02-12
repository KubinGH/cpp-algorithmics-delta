import os, random
try:
    os.mkdir("tests")
except FileExistsError:
    pass
for i in range(1, 6):
    with open("tests/test{}.in".format(i), "w") as file:
        w, h = random.randint(10, 1000), random.randint(10, 1000)
        x1, x2 = random.randint(0, w), random.randint(0, w)
        y1, y2 = random.randint(0, h), random.randint(0, h)
        file.write("{} {} {} {} {} {}".format(w, h, x1, y1, x2, y2))
    os.system("powierzchnia.exe < tests/test{}.in > tests/test{}.out".format(i, i))
