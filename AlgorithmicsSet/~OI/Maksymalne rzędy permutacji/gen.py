import sympy

N = 10**4+1
P = list(sympy.ntheory.primerange(0, N))
K = len(P)
Q = [[1 for _ in range(K+1)] for _ in range(N)]

with open(f"w{N}.txt", "w") as f:
    def fprint(*args, **kwargs):
        print(*args, **kwargs)
        return print(*args, **kwargs, file=f)
    for n in range(1, N):
        fprint(n, end=": ")
        for k in range(1, K+1):
            Q[n][k] = max(Q[n-1][k], Q[n][k-1] if k > 0 else 1)
            a = 1
            p = P[k-1]
            while p**a <= n:
                Q[n][k] = max(Q[n][k], Q[n-p**a][k-1] * p**a)
                a += 1
        fprint(max(Q[n]))
