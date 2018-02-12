import random
with open("t.txt", "w") as file:
    file.write("20000\n")
    for _ in range(20000):
        file.write("{} {}\n".format(random.randint(1, 3), random.randint(1, 3)))
