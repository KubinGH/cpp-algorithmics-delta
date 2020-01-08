import subprocess
from fractions import Fraction
import random

def call_with_io(command, string=''):
    return subprocess.run(
        command, input=string.encode(), capture_output=True,
        shell=True
    ).stdout.decode()

def solve(n, A):
    best = Fraction(0)
    for i in range(n):
        for j in range(i+1, n+1):
            best = max(best, Fraction(sum(A[i:j]), max(A[i:j])))
    return best

def randnz(a, b):
    x = random.randint(a, b)
    return x if x else randnz(a, b)

subprocess.run('rm inc && mkcxxO inc.cpp inc', shell=True)

for _ in range(1024):
    n = random.randint(1, 10)
    A = [randnz(-2, 5)**3 for _ in range(n)]

    exp = solve(n, A)
    got = Fraction(call_with_io('./inc', f"{n}\n{' '.join(str(x) for x in A)}").strip())

    print(A, "->", exp, "; got", got)
    if got != exp:
        break
