import random
import os

n = 10**5
q = 10**4
bounds = (1, 10**3)

for i in range(5, 6):
    with open("tests/test{}.in".format(i), "w") as file:
        file.write("{}\n".format(n))
        A = [random.randint(*bounds) for _ in range(n)]
        file.write("{}\n{}\n".format(" ".join(str(a) for a in A), q))
        for j in range(q):
            c = random.choice(("W", "Z"))
            if c == "W":
                l = random.randint(1, n - 1)
                a = random.randint(1, n - l)
                file.write("{} {} {}\n".format(c, a, a + l))
            elif c == "Z":
                a = random.randint(1, n)
                d = random.randint(-A[a-1]+1, A[a-1])
                A[a-1] += d
                file.write("{} {} {}\n".format(c, a, d))
    os.system("patyczki.exe < tests/test{0}.in > tests/test{0}.out".format(i))
