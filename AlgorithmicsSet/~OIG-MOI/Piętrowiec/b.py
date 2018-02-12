from math import log2, floor
def p(a, b):
    c = 0
    while a >= b:
        a -= b; b *= 2; c += 1
    return c

for i in range(1, 100):
    for j in range(1, 101):
        assert p(j, i) == floor(log2(j//i+1))
        print(j, i, p(j, i), floor(log2(j//i+1)))
