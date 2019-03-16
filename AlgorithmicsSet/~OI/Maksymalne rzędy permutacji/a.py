import sympy
import sys

N = 100

P = list(sympy.ntheory.primerange(0, N))

class SegmentTree:
    def __init__(self, n, op, identity):
        self.w = 2 ** ((2*n-1).bit_length() - 1)
        self.T = [identity for _ in range(2*self.w)]
        self.op, self.identity = op, identity

    def set(self, p, v):
        p += self.w
        self.T[p] = v
        while p > 1:
            p //= 2
            self.T[p] = self.op(self.T[2*p], self.T[2*p+1])

    def get(self, L, R):
        result = self.identity
        L += self.w; R += self.w + 1
        while L < R:
            if L % 2:
                result = self.op(result, self.T[L])
                L += 1
            if R % 2:
                R -= 1
                result = self.op(result, self.T[R])
            L //= 2; R //= 2
        return result

best = SegmentTree(N, max, 0)
best.set(0, 1)

def gen(i=0, a=0, c=1, s=0, N=N):
    if s >= N or best.get(0, s) > c:
        return
    if i == len(P):
        if s == 14:
            print((s, c))
        if best.get(s, s) < c:
            best.set(s, c)
        return
    if i < 3:
        print(f"{' '*i} {P[i]}**{a}")

    gen(i+1, 0, c, s)
    gen(i, a+1, c * P[i], s - (P[i]**a if a > 0 else 0) + P[i]**(a+1))

gen()

for p in range(N):
    print(p, best.get(p, p))
