from random import *
from pathlib import *
from shutil import *
import glob
from gamma import call_with_io

p = Path('./permutacja-testy/')
try:
    rmtree(p)
except FileNotFoundError:
    pass
p.mkdir()

def gen(n):
    t = [i + 1 for i in range(n)]
    shuffle(t)
    return f'{n}\n{" ".join(map(str, t))}\n'

for i in range(256):
    (p / f'{i}.in').write_text(gen(10))

for name in glob.glob("permutacja-testy/*.in"):
    with open(name[:-3] + ".out", "w") as file:
        file.write(call_with_io(f"permutacja.exe < {name}"))