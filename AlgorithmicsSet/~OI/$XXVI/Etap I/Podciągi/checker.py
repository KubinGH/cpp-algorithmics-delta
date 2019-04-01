import sys
import string
import collections

alphabet = string.ascii_lowercase + string.ascii_uppercase + string.digits

def check_solution(n, s):
    ls = collections.defaultdict(int)
    d = 1
    for i in range(len(s)):
        e, d = d, 2*d - ls[s[i]]
        ls[s[i]] = e
    return d == n, d

if __name__ == "__main__":
    data = [token for token in sys.stdin.read().split() if token]
    q = int(data[0])
    if len(data) != 2*q+1: 
        exit(1)
    for i in range(q):
        n, s = int(data[i+1]), data[q+i+1]
        r = check_solution(n, s)
        if not r[0]:
            print(f"Got {r[1]} instead of {n}", file=sys.stderr)
            exit(1)
    else:
        exit(0)
