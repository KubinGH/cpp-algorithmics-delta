import os, random

import sys
sys.path.append(r"C:\Program Files\AddToPath")
from gamma import TestFramework

class PavelTest(TestFramework):    
    filename_pattern = "tests/testd{i}.{ext}"
    n = 2*10**5
    bounds = (1, 10**9)
    k_bounds = (1, 10**9)
    iterable = range(25)
    self_test = False

    def generate_test(self):
        return ((self.n, random.randint(*self.k_bounds)), 
                [random.randint(*self.bounds) for _ in range(self.n)])
    
    def run_self_test(self, test):
        result = 0
        seq = test[1]
        n, k = test[0]
        for i in range(n):
            for j in range(i+1, n):
                if (seq[i] * seq[j]) % k != 0:
                    result += 1
        return result
    
    def save_test(self, file, test):
        print("{} {}".format(*test[0]), file=file)
        print(" ".join(str(x) for x in test[1]), file=file)
    
    def save_result(self, file, result):
        print(result, file=file)

if __name__ == "__main__":
    tester = PavelTest()
    tester.main()
