t = int(input().strip())

for _ in range(t):
    n, k = [int(x.strip()) for x in input().split()]
    A = [int(x.strip()) for x in input().split()]

    result = 0
    for i in range(n):
        for j in range(i+1, n+1):
            if max(A[i:j]) - (j - i) <= k and len(set(A[i:j])) == j - i:
                result += 1

    print(result)
