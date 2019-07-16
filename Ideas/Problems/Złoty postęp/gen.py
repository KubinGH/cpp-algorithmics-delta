from random import *


def random_sequence(n = 10, fib_chance = 0.8, r = range(1, 10), k = 2 ** 32):
    t = [choice(r), choice(r)]
    for i in range(2, n):
        t.append((t[i - 1] + t[i - 2]) % k if random() < fib_chance else choice(r) % k)
    return t

def random_queries(n, m = 20, set_chance = 0.1, r = range(1, 10), k = 2 ** 32):
    q = []
    for i in range(m):
        a = choice(range(n - 2))
        b = choice(range(a + 2, n))
        if random() < set_chance:
            q.append(('+', a, b, choice(r) % k))
        else:
            q.append(('?', a, b))
    return q

def readjustment_query(n, t):
    q = []
    while True:
        i = choice(range(2, n))
        add = t[i - 1] + t[i - 2] - t[i]
        if add < 0:
            continue
        q.append(('+', i, choice(range(i, n)), add))
        q.append(('?', i - 2, i))
        break
    return q

def to_str(t, q, k, nl='\n'):
    return (f"{len(t)} {len(q)} {k}\n{' '.join(map(str, t))}\n"
            f"{nl.join(' '.join(map(str, line)) for line in q)}")

def random_test(n = 10, m = 20, readjust = 2, kr = range(2, 100)):
    k = choice(kr)
    t = random_sequence(n, r = range(1, k), k = k)
    q = random_queries(n, m - 2 * readjust, r = range(1, k), k = k)
    for i in range(readjust):
        q += readjustment_query(n, t)
    return to_str(t, q, k)

def unpleasant(n = 10 ** 6, m = 10 ** 6 - 2, k = 10 ** 8 - 3):
    seq = [666, 42]
    for i in range(2, n):
        seq.append((seq[i - 1] + seq[i - 2]) % k)
    q = []
    for i in range(m):
        if i % 3 == 0:
            q.append(('+', 0, n - 1, i))
        elif i % 3 == 1:
            q.append(('+', 0, n - 1, k - i))
        else:
            a = randrange(0, n - 3)
            b = randrange(a + 2, n)
            q.append(('?', a, b))
    return to_str(seq, q, k)

# for i in range(5):
#    with open(f"./y{i}.in", 'w') as f:
#        f.write(random_test(10**6, 10**6, 100, kr = range(2, 10**9)))
with open(f"./z0.in", 'w') as f:
    f.write(unpleasant())
