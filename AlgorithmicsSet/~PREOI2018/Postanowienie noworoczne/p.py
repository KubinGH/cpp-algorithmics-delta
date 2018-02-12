import os, glob

for filename in glob.glob("tests/t*.p.out"):
    with open(filename, "r") as file:
        a = file.read()
    os.system("del {}".format(filename))
    with open("tests/t{}.out".format(filename[len("tests/t"):-len(".p.out")]), "w") as file:
        file.write(a)
