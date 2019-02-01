from itertools import permutations
import os
import tqdm

def test(n):
    wrong, lt, gt = 0, 0, 0
    for p in list(permutations(range(n))):
        out = f"{n}\n{' '.join(str(x) for x in p)}"
        with open("tmp.in", "w") as f: f.write(out)
        os.system("mel.exe < tmp.in > tmp.got.out 2> NUL")
        os.system("mel-brute.exe < tmp.in > tmp.exp.out 2> NUL")
        got, exp = open("tmp.got.out", "r").read().strip(), open("tmp.exp.out", "r").read().strip()
        got, exp = int(got), int(exp)
        if got != exp:
            print(p, got, exp)
            wrong += 1
            if got < exp:
                lt += 1
            else:
                gt += 1
    print("Total:", wrong, f"(got<exp: {lt}, got>exp: {gt})")
test(2)
