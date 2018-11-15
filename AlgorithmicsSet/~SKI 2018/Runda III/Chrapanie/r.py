import os, glob

for filename in glob.glob("tests-m/*.out"):
    os.rename(filename, filename.replace("\\out", "\\chr"))
