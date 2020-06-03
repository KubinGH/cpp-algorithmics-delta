import sys

for path in sys.stdin.read().split()[1:]:
    passed = set()

    x, y = 0, 0
    result = 0
    for c in path:
        if c == 'S': dx =  0; dy = -1
        elif c == 'N': dx =  0; dy = +1
        elif c == 'W': dx = -1; dy =  0
        elif c == 'E': dx = +1; dy =  0
        t = ((x, y), (x+dx, y+dy))
        if t[0] > t[1]:
            t = (t[1], t[0])
        if t in passed:
            result += 1
        else:
            result += 5
            passed.add(t)
        x += dx
        y += dy

    print(result)
