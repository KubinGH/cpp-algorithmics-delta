import math
import random

def generate1(N=32, Q=(5*10**3, 10**4), L=(2, 10**18), S=300):
    print("Begin generating type 1", (N, Q, L, S))
    def isprime(x):
        if x <= 1: return False
        for i in range(2, math.floor(math.sqrt(x))):
            if x % i == 0:
                return False
        else:
            return True
    primes = [p for p in range(1, 301) if isprime(p)]
    def walk(x=1, i=0, s=0):
        if i == len(primes):
            yield x
        else:
            p = primes[i]
            if random.randint(0, 1) == 1:
                if x * p <= L[1] and s + p <= S:
                    yield from walk(x * p, i, s + p)
                yield from walk(x, i + 1, s)
            else:
                yield from walk(x, i + 1, s)
                if x * p <= L[1] and s + p <= S:
                    yield from walk(x * p, i, s + p)
    def random_valide():
        while True:
            try:
                it = walk()
                for i in range(random.randint(1, 16)):
                    x = next(it)
                yield x
            except StopIteration:
                pass
    gen = random_valide()
    for t in range(N):
        print(f"tests/1/test{t}.in")
        q = random.randint(*Q)
        test = [next(gen) for _ in range(q)]
        with open(f"tests/1/test{t}.in", "w") as file:
            file.write(f"{q}")
            for n in test:
                file.write(f"\n{n}")
    print("Done.")

#generate1(32)

def generate2(L=(2, 10**18), S=300):
    print("Begin generating type 2", (L, S))
    P = [(i, j, 2**i - 2**j) for i in range(128) for j in range(128) if L[0] <= 2**i - 2**j <= L[1]]
    with open(f"tests/2/test.in", "w") as file:
        file.write(f"{len(P)}")
        for i, j, n in P:
            file.write(f"\n{n}")
    print("Done.")

#generate2()

def generate4():
    print("Begin generating type 4", ())
    with open(f"tests/4/test.in", "w") as file:
        file.write("999999")
        for n in range(2, 10**6+1):
            file.write(f"\n{n}")
    print("Done.")

#generate4()

def generate5(N=448, Q=(5*10**5, 10**6)):
    print("Begin generating type 5", (N, Q))
    for t in range(N):
        print(f"tests/5/test{t}.in")
        q = random.randint(*Q)
        test = [random.randint(2, 10**18) for _ in range(q)]
        with open(f"tests/5/test{64+t}.in", "w") as file:
            file.write(f"{q}")
            for n in test:
                file.write(f"\n{n}")
    print("Done.")

generate5()
