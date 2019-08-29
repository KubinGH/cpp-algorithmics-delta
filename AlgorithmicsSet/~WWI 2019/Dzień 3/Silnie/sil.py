import math

N = int(input()) + 1

n = 0
f = 1
result = 0

while N:
    n += 1
    f *= n
    result += min(N, n) * f
    N -= min(N, n)

print(result)
