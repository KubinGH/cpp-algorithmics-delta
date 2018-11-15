import glob

for filename in glob.glob("tests-strip/*.out"):
    cont = open(filename, "r").read()
    with open(filename, "w") as f:
        f.write(cont.split()[0])
    print("Done", filename)
