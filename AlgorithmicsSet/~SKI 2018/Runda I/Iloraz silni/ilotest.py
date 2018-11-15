from gamma import call_with_io
from math import factorial, sqrt, floor
from random import randint

for i in range(2**20):
    rt = floor(sqrt(i))
    b, a = sorted((randint(0, rt), randint(0, rt)))
    c = randint(1, 10**6)
    p = 1
    for x in range(b+1, a+1):
        p *= x; p %= c
    q = int(call_with_io("ilo.exe", f"{a} {b} {c}"))
    print(a, b, p, q)
    assert p == q
