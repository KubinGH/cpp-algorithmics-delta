n, k = [int(x) for x in input().split()]
def rs(n, k, r):
    if r == 1:
        return 1 / k**(n - 1)
    t = (r - 1) / r
    return (t * (t**n - 1) / (t - 1)) * (r / k)**n / ((r - 1) / k)
result = sum(rs(n, k, r) * r for r in range(1, k+1)) / k
print(f"{result:.6f}")
