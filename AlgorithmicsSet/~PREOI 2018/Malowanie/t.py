import os, random
import itertools

INSTANT_RUN = False
SELF_TEST = True 

test_filename = "tests/testb{i}.{ext}"
n = 10
max_c = 10
test_iterable = range(5)

def randtest(n=n, max_c=max_c):
    return [random.randint(1, max_c) for _ in range(n)]

def run_test(test):
    best = float("inf")
    for i in range(2**len(test)):
        i |= 1
        ci = i
        counter = 0; result = 0
        for b in range(len(test)-1, -1, -1):
            if i % 2:
                result += test[b]
                counter = 1
            else:
                result += counter
                counter += 1
            i //= 2
        best = min(best, result)
    return best

def str_test(test):
    string = ""
    string += "{}\n".format(n)
    string += " ".join(str(x) for x in test)
    return string

def str_result(result):
    if result is not None:
        return str(result)
    else:
        return "None"

for i in test_iterable:
    print("Generating test")
    test = randtest()
    result = None
    if SELF_TEST:
        result = run_test(test)
    if len(test) < 500: print(test, "->", result)
    print("Save file")
    with open(test_filename.format(i=i, ext="in"), "w") as file:
        file.write(str_test(test))
    with open(test_filename.format(i=i, ext="out"), "w") as file:
        file.write(str_result(result))
    if INSTANT_RUN and SELF_TEST:
        print("Test run")
        if SELF_TEST:
            os.system("thetacheck -a malowanie.exe -o {} > tmp.thetacheck.out".format(test_filename.format(i=i, ext="")[:-1]))
            if not open("tmp.thetacheck.out", "r").read().strip().endswith("(100.0%)"):
                break
        else:
            os.system("malowanie.exe < {}".format(test_filename))
if INSTANT_RUN:
    os.system("del tmp.thetacheck.out")
