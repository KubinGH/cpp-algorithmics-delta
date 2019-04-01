from gamma import call_with_io
import tqdm
import os
import time

T = 2**16
use_tqdm = True

it = tqdm.tqdm(range(T)) if use_tqdm else range(T)
def tprint(*args, **kwargs): 
    if not use_tqdm: print(*args, **kwargs)

times = []
for i in it:
    tprint(f"Test {i}")

    r = call_with_io("nie-di.exe", f"{a}\n{b}")

print()
#print("Times:", times)

os.system("pause")
