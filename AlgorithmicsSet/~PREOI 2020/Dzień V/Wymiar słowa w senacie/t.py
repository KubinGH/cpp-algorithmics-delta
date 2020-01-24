import os, subprocess
import random
import math

def call_with_io(command, string):
    return subprocess.run(
        command, input=string.encode(), capture_output=True, shell=True
    ).stdout.decode()

os.system("mkcxxO wss.cpp wss")
os.system("mkcxxO wssb.cpp wssb")

class Test:
    def __init__(self):
        n = random.randint(1, 100)
        self.S = "".join(random.choice("abc") for _ in range(n))
        print("!", self.S)
        for i in range(n):
            i += 1
            if not random.randint(0, 4):
                d = random.randint(1, math.floor(math.sqrt(i)))
                self.S = self.S[:i-d] + self.S[:d][::-1] + self.S[i:]
                print(i, d, ">", self.S)

    def str(self):
        return f"{len(self.S)}\n{self.S}"
    def get(self):
        return [int(x) for x in call_with_io("./wss" , self.str()).strip().split()]
    def exp(self):
        return [int(x) for x in call_with_io("./wssb", self.str()).strip().split()]

for _ in range(10**7):
    t = Test()
    print(t.str())
    print(t.get())
    print(t.exp())
    assert t.get() == t.exp()
