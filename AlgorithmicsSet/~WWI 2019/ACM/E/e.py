from functools import lru_cache
import bisect

tuples = [(2, 3, 5), (0, ), (1, 3), (1, 5), (0, ), (1, 3), (1, 2, 3, 5), (0, ), (1, 3), (1, 2, 3, 5), (0, ), (1, 3), (1, 2, 3, 5), (0, ), (1, 3), (1, 2, 3, 5), (0, ), (1, 3), (1, 2, 3, 5), (0, ), (1, 3)]

@lru_cache(maxsize=None)
def generate(n, lz):
    if n == 0:
        return [""]
    rt = []
    if lz:
        rt.extend(s for s in generate(n - 1, lz))
    for x in tuples[n - 1]:
        if x or not lz:
            rt.extend(str(x)+s for s in generate(n - 1, False))
    return rt

#N = generate(len(tuples), True)

#N = [int(x) for x in N if x]

N = [int(x) for x in open('f.txt', 'r').read().split() if x]

N.sort()

import num2words

for n in N:
    #print(n, num2words.num2words(n, lang='pl'))
    assert 'e' not in num2words.num2words(n, lang='pl')

exit(0)


import sys

data = sys.stdin.read()

ints = [int(x) for x in data.split()]

q = ints[0]

for i in range(q):
    a, b = ints[2*i+1], ints[2*i+2];
    print(bisect.bisect_right(N, b) - bisect.bisect_left(N, a))
