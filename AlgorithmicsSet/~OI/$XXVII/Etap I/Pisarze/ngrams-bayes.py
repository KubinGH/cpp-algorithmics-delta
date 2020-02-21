import math
import random
import itertools
import collections

import pis1

K = 3
def ngrams(text, k):
    return (text[i:i+k] for i in range(len(text)-k+1))

names = ["Mickiewicz", "Prus", "Sienkiewicz"]
texts = [open(f"{name}.txt", "r").read() for name in names]

weights = [collections.defaultdict(lambda: math.log(1)) for _ in range(3)]

print(f"K = {K}")
for i in range(3):
    print(f"{K}-grams: {names[i]}")
    text = texts[i].lower()#.replace(' ', '  ')
    cnt = collections.Counter()
    tot = 0
    for t in ngrams(text, K):
        cnt[t] += 1
        tot += 1
    print(len(cnt))
    for t, c in cnt.most_common(3000):
        weights[i][t] = math.log(c / tot)
print(f"{K}-grams done")

def normalize(it):
    s = sum(it)
    return [x/s for x in it]
def classify(text):
    return [sum(weights[i][t] for t in ngrams(text, K)) for i in range(3)]
def normclassify(text):
    return normalize([math.exp(p) for p in classify(text)])
def argmax(it):
    return max(zip(it, itertools.count(0)))[1]
def identify(text):
    return names[argmax(classify(text))]

from pistestgen import gen

ok, total = 0, 0

X, Y = gen(4, 32)
for x, y in zip(X, Y):
#    if len(x) <= 60:
    yy = identify(x)
    print('', normclassify(x))
#    else:
#        yy = pis1.solve(x)
    if y == yy:
        ok += 1
    total += 1

print(ok, "/", total, "=", round(ok/total, 3))
