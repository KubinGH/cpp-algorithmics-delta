def O(n):
    A = []
    for i in range(1, n+1):
        A.append(i)
        A.append(-1)
    A.pop()
    while -1 in A:
        A[-(A[::-1].index(-1)+1)] = A.pop()
    return A
