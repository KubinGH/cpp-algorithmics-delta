import os, random

n = 500000
bounds = (1, 100000)

while True:
    A = [random.randint(*bounds) for _ in range(n)]
    s = "{}\n{}".format(n, " ".join(str(x) for x in A))
    with open("temp/temp.in", "w") as file:
        file.write(s)    
    if n <= 100:
        print(s)
    os.system("rarity.exe < temp/temp.in > temp/got.temp.out")
    os.system("rarity-brute.exe < temp/temp.in > temp/expected.temp.out")
    got = open("temp/got.temp.out").read().strip()
    expected = open("temp/expected.temp.out").read().strip()
    print("+" if got == expected else "-", got, expected)
    if got != expected:
        break
