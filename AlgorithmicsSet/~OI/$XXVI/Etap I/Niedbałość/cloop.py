from checker import check_solution
from t import CarelessTester
from gamma import call_with_io
from itertools import combinations, chain
import tqdm
import os
import time

T = 2**16
use_tqdm = True

def all_combinations(it): return chain.from_iterable(combinations(it, n) for n in range(len(it)+1))

gen = CarelessTester()

alphabet = "ATCG"
alphabet_subsets = [s for s in all_combinations(alphabet) if len(s) > 1]
N = (2, 128)

it = tqdm.tqdm(range(T)) if use_tqdm else range(T)
def tprint(*args, **kwargs): 
    if not use_tqdm: print(*args, **kwargs)

times = []
for i in it:
    A = "".join(alphabet_subsets[i%len(alphabet_subsets)])
    tprint("Alphabet", A)
    tprint(f"Test {i}")
    a, b = "", ""
    while not (set(a) & set(b)):
        a, b = gen.generate_test(N, A).split("\n")
    tprint(a, b)
    start = time.time()
    r = call_with_io("nie-di.exe", f"{a}\n{b}")
    times.append(time.time() - start)
    tprint("-> ", r)
    s, w = check_solution(a, b, r)
    if w:
        print()
        print("!@#")
        print("Witnesses:", w)
        if use_tqdm:
            print(a, b, r)
        break
    else:
        tprint("+")

print()
#print("Times:", times)

os.system("pause")
