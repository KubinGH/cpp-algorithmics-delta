import os

V = [6, 2, 5, 5, 4, 5, 6, 3, 7, 6, 6]

def d(n):
    if n == 0:
        return V[0]
    r = 0
    while n:
        r += V[n % 10]
        n //= 10
    return r

f = {}
for i in range(10**7+1):
    c = d(i)
    if c not in f:
        f[c] = i

for k, v in f.items():
    print(k, "->", v)
