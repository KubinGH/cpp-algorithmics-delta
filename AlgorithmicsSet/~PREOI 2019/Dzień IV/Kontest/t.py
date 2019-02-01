with open("tmp.in", "w") as f:
    f.write(f"{10**9} {10**4} {10**9}\n")
    for i in range(1, 10**4+1):
        f.write(f"{i} {i} {10**9}\n")