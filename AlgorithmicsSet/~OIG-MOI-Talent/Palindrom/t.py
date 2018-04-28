import random
L = list(range(1, 10**5+1)) * 2
random.shuffle(L)
with open("t.txt", "w") as file:
    file.write("200000\n")
    file.write(" ".join(str(i) for i in L))
