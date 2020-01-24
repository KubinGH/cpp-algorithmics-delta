import itertools
from random import randint

M = 10**18

powers = set()
for k in itertools.count(4):
    if 2**k > M:
        break
    for x in itertools.count(1):
        if x**k > M:
            break
        powers.add(x**k)

print(len(powers))


def iroot(n, k):
    r = int(n ** (1/k))
    for d in range(-10, 11):
        if (r+d)**k == n:
            return r+d
    else:
        return None

print(iroot(10**18, 6))

for test in range(1000):
    print(test)
