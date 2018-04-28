import random
a = random.sample(range(1, 10**9), 10**5)
b = random.sample(range(1, 10**9), 10**5)
with open("t.txt", "w") as file:
    file.write("100000\n")
    for x, y in zip(a, b):
        file.write("{} {}\n".format(x, y))
