import numpy

def pairwise_sums(A, B):
    if len(A) == 0 or len(B) == 0: return set()
    lo, hi = min(min(A), min(B)), max(max(A), max(B))
    P, Q = numpy.zeros(hi-lo+1, dtype=numpy.int32), numpy.zeros(hi-lo+1, dtype=numpy.int32)
    for a in A: P[(hi-lo)-(a-lo)] = 1
    for b in B: Q[(hi-lo)-(b-lo)] = 1
    R = numpy.polymul(P, Q)
    print(P)
    print(Q)
    print(R)
    C = {i+2*lo for i, r in enumerate(reversed(R)) if r > 0}
    #print(list(A), "#", list(B), "->", sorted(C))
    return C

def pairwise_sums_brute(A, B):
    R = set()
    for a in A:
        for b in B:
            R.add(a + b)
    return R

print(pairwise_sums([1, 2, 3], [5, 3, 1, -1]))
print(pairwise_sums_brute([1, 2, 3], [5, 3, 1, -1]))
exit()

def pairwise_diffs(A, B):
    return pairwise_sums(A, [-b for b in B])

def get_lengths(A):
    n = len(A)
    e = []
    s = 0
    for i, a in enumerate(A):
        s = (s + a) % 2
        if s == 1:
            e.append(i+1)
    # odd, even indices
    E, F = numpy.zeros(len(e), dtype=numpy.int32), numpy.zeros((n+1) - len(e), dtype=numpy.int32)
    p, q = 0, 0
    for i in e:
        E[p] = i; p += 1
        for j in range(E[p-2]+1 if p > 1 else 0, E[p-1]):
            F[q] = j; q += 1
    for j in range(E[p-1]+1 if p > 0 else 0, n+1):
        F[q] = j; q += 1
    # odd, even
    P = set(pairwise_diffs(E, F)) | set(pairwise_diffs(F, E))
    P = {p for p in P if 1 <= p <= n}
    Q = set(pairwise_diffs(E, E)) | set(pairwise_diffs(F, F))
    Q = {q for q in Q if 1 <= q <= n}
    return P, Q

q = int(input())

for _ in range(q):
    n, m = input().split()
    n, m = int(n), int(m)
    A, B = numpy.zeros(n, dtype=numpy.int32), numpy.zeros(m, dtype=numpy.int32)
    for i, a in enumerate(input().split()):
        A[i] = int(a) % 2
    for i, b in enumerate(input().split()):
        B[i] = int(b) % 2
    P, Q = get_lengths(A)
    R, S = get_lengths(B)
    result = 0
    for d in P:
        if d in R:
            result = max(result, d)
    for d in Q:
        if d in S:
            result = max(result, d)
    print(result)
