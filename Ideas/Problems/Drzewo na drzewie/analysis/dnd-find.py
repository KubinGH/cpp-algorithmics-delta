import math

def is_prime(x):
    if x == 0 or x == 1: return False
    if x == 2 or x == 3: return True
    for d in range(2, math.floor(math.sqrt(x))+1):
        if x % d == 0:
            return False
    else:
        return True

'''
for i in range(1<<17, (1<<18)+1):
    if is_prime(i):
        S = set()
        c = 1
        while c not in S:
            S.add(c)
            c *= 2
            c %= i
        print(i, "->", len(S))
        if bin(len(S)).count("1") == 1:
            break
'''

p = 169831
# len(S) = 333
c = 1
S = set()
while c not in S:
    S.add(c)
    c *= 2
    c %= p
print(sorted(S))
print(pow(2, len(S), p), c)