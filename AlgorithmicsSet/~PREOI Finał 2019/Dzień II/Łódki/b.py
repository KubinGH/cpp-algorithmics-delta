import itertools

A = [0, 1, 4, 2, 2, 3]
B = [-1, 2, 10, 6, 2, 4]

ranges = [itertools.chain(range(a, b+1), (0,)) for a, b in zip(A, B)]
result = 0
total = 0
for seq in itertools.product(*ranges):
    print(seq)
    if not any(x for x in seq):
        continue
    mx = 0
    for x in seq:
        if x and x <= mx:
            break
        else:
            mx = max(x, mx)
    else:
        print("+")
        result += 1
    total += 1

print(result, "/", total)
