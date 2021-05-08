n, k = [int(x) for x in input().split()]
result = sum(sum(((r-1)/k)**(i-1) * (r/k)**(n-i) for i in range(1, n+1)) * r for r in range(1, k+1)) / k
print(f"{result:.6f}")
