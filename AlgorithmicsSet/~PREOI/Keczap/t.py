import os, random
import itertools

INSTANT_RUN = False
SELF_TEST = False 

test_filename = "tests/testf{i}.{ext}"
n = 10**5
q = 2*(10**5)
max_growth = 8000
test_iterable = range(5)

def randtest(n=n, q=q):
    result = []
    for _ in range(q):
        com = "WINCYJ" if random.randint(0, 1) else "KECZAP"
        if com == "WINCYJ":
            result.append((com, random.randint(1, n), random.randint(1, max_growth)))
        else:
            i = random.randint(1, n-1)
            j = random.randint(i, n)
            result.append((com, i, j, random.randint(1, 5)))
    return result

for i in test_iterable:
    print("Generating test")
    test = randtest()
    result = None
    if SELF_TEST:
        result = []
        arr = [0 for _ in range(n)]
        print("Test self")
        for p in test:
            if p[0] == "WINCYJ":
                arr[p[1]-1] += p[2]
            elif p[0] == "KECZAP":
                r = 0
                for d in range(p[1]-1, p[2]):
                    if arr[d] % p[3] == 0:
                        r += 1
                result.append(r)
    if len(test) < 500: print(test, "->", result)
    print("Save file")
    with open(test_filename.format(i=i, ext="in"), "w") as file:
        file.write("{} {}\n".format(n, q))
        for p in test:
            file.write("{}\n".format(" ".join(str(x) for x in p)))
    with open(test_filename.format(i=i, ext="out"), "w") as file:
        if result is not None:
            file.write("\n".join(str(s) for s in result))
        else:
            file.write("None")
    if INSTANT_RUN and SELF_TEST:
        print("Test run")
        if SELF_TEST:
            os.system("thetacheck -a keczap.exe -o {} > tmp.thetacheck.out".format(test_filename.format(i=i, ext="")[:-1]))
            if not open("tmp.thetacheck.out", "r").read().strip().endswith("(100.0%)"):
                break
        else:
            os.system("keczap.exe < {}".format(test_filename))
if INSTANT_RUN:
    os.system("del tmp.thetacheck.out")
