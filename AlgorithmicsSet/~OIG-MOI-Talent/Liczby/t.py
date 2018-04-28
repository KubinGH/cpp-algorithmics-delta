import math

def popcount(n):
    return bin(n)[2:].count("1")

def spop(n):
    return sum(popcount(i) for i in range(1, n+1))

n = 6
T = [0 for _ in range(n+1)]

for i in range(1, 2**n+1):
    b = bin(i)[2:]
    for j in range(len(b)):
        if b[-j-1] == "1":
            T[j] += 1
    t = 0
    for j in range(len(b)):
        if b[-j-1] == "1":
            t += spop(2**j)
    print(i, T, spop(i))
