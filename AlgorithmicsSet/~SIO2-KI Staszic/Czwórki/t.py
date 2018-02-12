with open("t.txt", "w") as file:
    print("{}\n{}".format(5000, " ".join(str(i) for i in range(0, 500001, 100))), file=file)
