from gamma import call_with_io
import random
from string import ascii_lowercase

for i in range(1<<18):
    if i % 32 == 0:
        print(i)
    n = 2 * random.randint(1, 4)
    s = [random.choice(ascii_lowercase) for _ in range(n//2)]
    s += s[::-1]
    b = random.randint(0, 1)
    if b:
        for _ in range(random.randint(1, n//2)):
            i = random.randint(0, n//2-1)
            j = 2*(n//2-1) - i + 1
            s[i], s[j] = random.sample(ascii_lowercase, 2)
    s = "".join(s)
    print(s)
    m = random.choice((0, n))
    r = call_with_io("pal.exe", f"{m}\n" + s)
    assert r == "TAK" or r == "NIE"
    print(b, r)
    assert b == (r == "NIE")
