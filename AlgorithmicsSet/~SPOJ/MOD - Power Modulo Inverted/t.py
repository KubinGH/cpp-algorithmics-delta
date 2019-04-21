import random
import subprocess

def call_with_io(command, string):
    return subprocess.run(command, input=string, encoding="utf-8", capture_output=True).stdout

for i in range(128):
    x, z, k = [random.randint(1, 10**9) for _ in range(3)]
    d = f"{x} {z} {k}\n0 0 0\0"
    y1 = call_with_io("./mod.exe", d).strip()
    y2 = call_with_io("./mod2.exe", d).strip()
    print(f"{i}: {x}, {z}, {k} -> {y1} {y2}", flush=True)
    assert y1 == y2