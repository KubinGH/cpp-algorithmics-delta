from collections import defaultdict
c = defaultdict(set)
with open("CPairsE.txt", "r") as f:
    for line in f.readlines():
        if line:
            a, b = line.split()
            c[int(a)].add(int(b))
P = 1
def isprime(k):
    if k <= 1: return False
    if k <= 3: return True
    for i in range(2, k):
        if i*i > k: break
        elif k % i == 0:
            return False
    return True
for k in c:
    if isprime(k):
        P *= (k - len(c[k])) / k
print(P)
#for k in sorted(c):
#    print(k, sorted(c[k]))