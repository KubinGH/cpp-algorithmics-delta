from gamma import call_with_io
import random

for i in range(100):
    n, k = random.randint(1, 100), random.randint(1, 50)
    a = call_with_io("rownanie.exe", f"{n} {k}")
    b = call_with_io(r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-delta\AlgorithmicsSet\~Wrocławskie Sparingi\Równanie Jasia\brute\rownanie-brute.exe", 
                     f"{n} {k}")
    print(f"{n} {k} -> {a}/{b}")
    if a != b:
        break