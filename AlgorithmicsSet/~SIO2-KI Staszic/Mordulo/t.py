import random
m = 300000
with open("t.in", "w") as file:
    print("{} {}".format(m, m), file=file)
    print(" ".join(str(random.randint(1, 2**64 - 1)) for _ in range(m)), file=file)
    print(" ".join(str(random.randint(1, 2**64 - 1)) for _ in range(m)), file=file)
