import os, glob, time

mem = {"kB": 1024, "MB": 1024**2}
M = 0
ctime = time.time()
for a in sorted(glob.glob("**/*", recursive=True), key=os.path.getsize):
    size = os.path.getsize(a)
    date = os.path.getmtime(a)
    minutes, days = round((ctime - date)/60, 2), round((ctime - date)/(60*60*24), 2)
    print(f"{a} | {size} | {minutes}min = {days}d")
    M += size
    if ".cpp" not in a and days > 30 and size > 0.5*mem["MB"]:
        prompt = input("Remove? (yes for True): ")
        if prompt == "yes":
            os.remove(a)
print(f"M = {M}B = {round(M/mem['kB'], 2)}kB = {round(M/mem['MB'], 2)}MB")
os.system("pause")