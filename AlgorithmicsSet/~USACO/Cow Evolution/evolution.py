import sys
import functools
sys.stdin = open("evolution.in", "r")
#sys.stdout = open("evolution.out", "w")

n = int(input())
flags = [set(input().split()[1:]) for _ in range(n)]

def build(F):
    if not F or F == [set()]:
        return set()
    all_union = functools.reduce(lambda a, b: a | b, F, set())
    for split in all_union:
        F_with = [f for f in F if split in f]
        F_without = [f for f in F if split not in f]
        a, b = build([f - {split} for f in F_with]), build(F_without)
        if a is not None and b is not None and not (a & b):
            return a | b | {split}
    else:
        return None

print("yes" if build(flags) is not None else "no")
