import heapq

H, W, n = [int(x) for x in input().split()]

X, Y = [0]*n, [0]*n

for i in range(n):
    p = input().split()
    X[i] = int(p[0])
    Y[i] = int(p[1])

done = [False for _ in range(n)]
opt = [4 << (max(W, H)) for _ in range(n)]
track =  [-1 for _ in range(n)]

opt[0] = 0

heap = []
heapq.heappush(heap, (0, 0))

while heap:
    u = heap[0][1]
    heapq.heappop(heap)
    if done[u]: continue
    done[u] = True
    for v in range(n):
        if not done[v]:
            w = max(abs(X[u] - X[v]), abs(Y[u] - Y[v]))
            if opt[u] + (1 << w) < opt[v]:
                opt[v] = opt[u] + (1 << w)
                track[v] = u
                heapq.heappush(heap, (opt[v], v))

result = []
u = n - 1
while u != -1:
    result.append(u)
    u = track[u]

print(len(result))
print(" ".join(str(x+1) for x in reversed(result)))
