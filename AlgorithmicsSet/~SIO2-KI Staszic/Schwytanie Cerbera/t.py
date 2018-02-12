n = 10**6
with open("t.txt", "w") as file:
    file.write("{} {}".format(n, " ".join(str(i) for i in range(n))))
