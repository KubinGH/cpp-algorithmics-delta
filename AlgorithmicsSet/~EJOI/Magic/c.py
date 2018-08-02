import os, glob

for file in glob.glob("tests/*.sol"):
    print(file)
    os.rename(file, file[:-4] + ".out")
    
os.system("pause")