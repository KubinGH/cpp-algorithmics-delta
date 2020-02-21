import subprocess
import sys
from collections import Counter

def call_with_io(command, string):
    return subprocess.run(
        command, input=string.encode(), capture_output=True,
        shell=True, timeout=5
    ).stdout.decode()

def pt(t, p):
    if p >= 0.9*t: return 100
    elif p <= t/3: return 0
    else: return 100 * (p - t/3)/(0.9*t - t/3)

assert len(sys.argv) >= 2
sol = sys.argv[1]
if len(sys.argv) >= 3:
    groups = [sys.argv[2]]
    modifiers = [1]
else:
    groups = [1, 2, 3, 4]
    modifiers = [0.2, 0.2, 0.3, 0.3]

stat = [Counter() for _ in range(4)]
runs = 10
totpoints = 0

for i in range(runs):
    gpoints = []
    points = 0
    for group, mod in zip(groups, modifiers):
        subprocess.run(f"python pistestgen-base.py {group} tests/tmp .", shell=True)

        got = call_with_io(f"python {sol}.py", open("tests/tmp.in", "r").read()).strip().split('\n')
        exp = open("tests/tmp.out", "r").read().strip().split('\n')

        assert len(got) == len(exp)
        total = len(exp)
        ok = sum(a == b for a, b in zip(got, exp))

        for a, b in zip(got, exp):
            if a != b:
                stat[group-1][a, b] += 1

        gpoints.append(pt(total, ok) * mod)
        points += gpoints[-1]

    print(f"{round(points, 1)} {[round(p, 1) for p in gpoints]}")
    totpoints += points

print("Statistics")
for g in range(4):
    print("Group", g+1)
    for a, b in sorted(stat[g]):
        print(f"{a: >11} instead of {b: >11}:\t{stat[g][a, b]} times")
print(f"Average --> {round(totpoints/runs, 1)}")
