import os
import random
import itertools

import sys
sys.path.append(r"C:\Program Files\AddToPath")
from gamma import TestFramework

class WybrakowanaPermutacjaTester(TestFramework):
    save_tests = True
    self_test = False
    iterable = range(5)
    filename_pattern = "tests/testc{i}.{ext}"
    n = 10**5
    zero_chance = 3
    def generate_test(self, n=n):
        t = list(range(1, n + 1))
        random.shuffle(t)
        s = random.randint(0, n)
        t[0:s] = [0] * s
        random.shuffle(t)
        return t

    def run_self_test(self, test):
        self.save_test(open("temp.in", "w"), test)
        os.system("jonaszobrute.exe < temp.in > temp.out")
        with open("temp.out", "r") as file:
            result = int(file.read().strip())
        os.system("del temp.in & del temp.out")
        return result

    def save_test(self, file, test):
        file.write("{}\n".format(self.n))
        file.write(" ".join(str(t) for t in test))

    def save_result(self, file, result):
        file.write(str(result))

if __name__ == "__main__":
    tester = WybrakowanaPermutacjaTester()
    tester.main()
