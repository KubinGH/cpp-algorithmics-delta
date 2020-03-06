import random

n = 4
m = random.randint(1, n**2)

tiles = [(x, y) for x in range(n) for y in range(n)]
t = random.sample(tiles, m)

print(n, m)
for x, y in t:
    print(x+1, y+1)
