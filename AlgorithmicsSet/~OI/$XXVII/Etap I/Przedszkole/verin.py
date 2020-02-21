import glob
import collections

def verify(indata):
    lines = indata.split('\n')
    n, m, z = [int(x) for x in lines[0].split()]
    edges = [tuple(int(u) for u in line.split()) for line in lines[1:m+1]]
    queries = [int(k) for k in lines[m+1:]]

    if any(len(e) != 2 for e in edges):
        return "malformed edge"
    if any(not (1 <= u <= n and 1 <= v <= n) for u, v in edges):
        return "vertex out of range"
    if any(u == v for u, v in edges):
        return "edge is a loop"
    if len(queries) != z:
        return "bad query count"
    if any(not (1 <= k <= 10**9) for k in queries):
        return "query param out of range"

    degree = collections.defaultdict(int)
    edgeset = set()
    for u, v in edges:
        if u > v: u, v = v, u
        degree[u] += 1
        degree[v] += 1
        if (u, v) in edgeset:
            return "repeat edge"
        edgeset.add((u, v))

    if n > 15 and m > 24 and not all(x == 2 for x in degree.values()):
        return "no matching subtask"

for n in sorted(glob.glob('tests*/in/*.in')):
    print(n, end=" ")
    st = verify(open(n, 'r').read())
    if st:
        print(st)
    else:
        print(end='\r')
