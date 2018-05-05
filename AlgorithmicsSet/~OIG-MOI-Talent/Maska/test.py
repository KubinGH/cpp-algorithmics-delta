import subprocess
import random
from gamma import call_with_io

def main(command="liczba-min.exe", verbose=True):
    for i in range(100):
        h, d, s = [random.randint(1, 40000) for _ in range(3)]
        got = int(call_with_io(command, f"{h} {d} {s}"))
        exp = sorted([h, d, s])[1] // 2
        if got != exp:
            print(f"{i}:", h, d, s)
            print(f"{got} != {exp}")
            print("!@#")
            return False
        else:
            pass
    return True