import subprocess
import random
from gamma import call_with_io

def main(command="liczba-min.exe", verbose=True):
    for i in range(100):
        p, k, s, d = [random.randint(*b) for b in [(1, 30), (1, 20), (0, 59), (1, 100)]]
        got = int(call_with_io(command, f"{p} {k} {s} {d}"))
        exp = (60*k+s-d)//p
        if exp < 0: continue
        if got != exp:
            print(f"{i}:", p, k, s, d)
            print(f"{got} != {exp}")
            print("!@#")
            return False
        else:
            pass
    return True