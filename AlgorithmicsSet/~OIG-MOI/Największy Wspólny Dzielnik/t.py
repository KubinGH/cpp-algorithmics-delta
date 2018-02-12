import os, glob

for filename in glob.glob("tests/*.in"):
    os.system("gcd.exe < {} > {}".format(filename, os.path.splitext(filename)[0] + ".out"))
