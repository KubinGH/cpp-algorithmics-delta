import math

def is_prime(x):
    if x <= 1: return False
    elif x <= 3: return True
    for d in range(2, math.floor(math.sqrt(x)) + 1):
        if x % d == 0:
            return False
    return True

for p in (x for x in range(2, 100+1) if is_prime(x)):
    print(p)
    for i in range(5):
        def cut(c): return (c % 10**(i+1)) // 10**i 
        S = {cut(p*k) for k in range(10**i)}
        print(S)
