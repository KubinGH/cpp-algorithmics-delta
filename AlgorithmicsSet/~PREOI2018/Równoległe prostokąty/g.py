with open("tests/testg0.in", "w") as file:
    file.write("99856\n")
    for y in range(316):
        for x in range(316):
            file.write("{} {}\n".format(x, y))

with open("tests/testg0.out", "w") as file:
    file.write("2477052900")    
