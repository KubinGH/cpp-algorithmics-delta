from random import randint
from itertools import product

def func(k=6):
    vals = sorted([sum(4**i * x[i] for i in range(len(x))) for x in product((-1, 0, 1), repeat=k)])
    vals = [v for v in vals if v >= 0]
    return vals

def find_up(a, b, vals):
    i = a
    while i < b and i not in vals:
        i += 1
    return i if i in vals else None

def find_down(a, b, vals):
    i = b
    while i > a and i not in vals:
        i -= 1
    return i if i in vals else None

def result(a, b, vals):
    i = find_up(a, b, vals)
    j = find_down(a, b, vals)
    print("i", i, "j", j)
    if i is None or j is None: return 0
    return vals.index(j) - vals.index(i) + 1

def randtest(k=10):
    vals = func(k)
    while True:
        input(">>")
        a = randint(1, vals[-1] - 1)
        b = randint(a + 1, vals[-1])
        print("{} {}".format(a, b))
        print(result(a, b, vals))
