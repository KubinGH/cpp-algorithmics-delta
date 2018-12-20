from itertools import product

def x(n, m, k):
    R = []
    for l in range(n+1):
        r = 0
        for s in product(list(range(m)), repeat=l):
            r += all(len(set(s[i:i+k+1]))>1 for i in range(l-k))
        R.append(r)
    return R

def f(n, m, k):
    R = []
    for l in range(k, n+1):
        r = 0
        for s in product(list(range(m)), repeat=l):
            b = sum(len(set(s[i:i+k]))==1 for i in range(l-k+1)) == 1
            r += b
        R.append(r)
    return R

n, m, k = 10, 5, 2

print(f(n, m, k))
