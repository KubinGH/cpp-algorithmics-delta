import random

def solve(n, P, t=10**5):
    approx = 0
    for t in range(t):
        c = [0 for _ in range(5)]
        for i in range(n):
            x = random.choices([0, 1, 2, 3, 4], P)[0]
            c[x] += 1
        if c == [n//5 for _ in range(5)]:
            approx += 1
    return approx / t

print(solve(20, [20, 20, 20, 20, 20]))
