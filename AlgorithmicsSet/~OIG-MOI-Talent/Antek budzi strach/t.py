from os import system
from random import randint
from math import sqrt

for i in range(1, 301):
    root = int(sqrt(i))
    a, b = randint(-root, root), randint(-root, root) 
    with open("temp/tmp.in", "w") as file:
        file.write("{} {}".format(a, b))
    system("antek_strachobudzacy.exe < temp/tmp.in > temp/tmp.got.out")
    got = open("temp/tmp.got.out", "r").read().strip() == "TAK"
    exp = abs(a) == abs(b)
    print(a, b, got, exp)
    if got != exp:
        break
