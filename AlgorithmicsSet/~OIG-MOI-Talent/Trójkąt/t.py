n = 2*(10**5)
with open("t.txt", "w") as file:
    file.write("{} {}".format(n, " ".join("1" if 0 < i < n-1 else "1000000000" for i in range(n))))
