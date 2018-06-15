import glob
print(len(glob.glob("**\*.cpp", recursive=True)))