import subprocess
from itertools import chain, combinations
import random

def call_with_io(command, string=""):
    bytes_input = string.encode("utf-8")
    process = subprocess.run(command, shell=True, input=bytes_input, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    result = process.stdout.decode("utf-8", errors="replace").replace("\r\n", "\n")
    return result

'''
def X(A, d):
	x = 0
	for ch in chain(combinations(A, i) for i in range(1, len(A)+1)):
		for c in ch:
			if max(c) - min(c) < d:
			    x += 1
	return x
'''

def X(A, d):
    x = 0
    j = 0
    for i in range(len(A)):
        while j < i and A[i] - A[j] >= d:
            j += 1
        x += 2 ** (i - j)
    return x

def t(x, d):
    #print(x, d)
    out = call_with_io("counting.exe", f"{x} {d}")
    A = [int(x) for x in out.split()[1:]]
    #print(A)
    ox = X(A, d)
    #print(ox)
    try:
        assert not A or (ox == x and len(A) <= 10**4 and max(A) < 10**18)
    except AssertionError as e:
        print(x, d, len(A), ox)
        raise e
    if not A:
        print(x, d, -1)

for i in range(1000):
    x, d = random.randint(1, 10**9), random.randint(1, 10**9)
    print(x, d)
    t(x, d)