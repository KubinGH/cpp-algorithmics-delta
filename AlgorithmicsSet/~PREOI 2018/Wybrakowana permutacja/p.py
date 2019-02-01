import os, glob

for filename in glob.glob("tests/test*.p.out"):
    with open(filename, "r") as file:
        a = file.read().split()[0]
    os.system("del {}".format(filename))
    with open("tests/test{}.out".format(filename[len("tests/test"):-len(".p.out")]), "w") as file:
        file.write(a)
