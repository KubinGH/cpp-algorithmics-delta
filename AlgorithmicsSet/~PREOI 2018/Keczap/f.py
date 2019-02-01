import os, random

import sys
sys.path.append(r"C:\Program Files\AddToPath")
from gamma import TestFramework

class KetchupTest(TestFramework):    
    filename_pattern = "testsf/test{i}.{ext}"
    n = 100
    q = 200
    max_growth = 20
    iterable = range(10)

    def generate_test(self):
        result = []
        for _ in range(self.q):
            com = "WINCYJ" if random.randint(0, 1) else "KECZAP"
            if com == "WINCYJ":
                result.append((com, random.randint(1, self.n), random.randint(1, self.max_growth)))
            else:
                i = random.randint(1, self.n-1)
                j = random.randint(i, self.n)
                result.append((com, i, j, random.randint(1, 5)))
        return result

    def run_self_test(self, test):
        result = []
        arr = [0 for _ in range(self.n)]
        for p in test:
            if p[0] == "WINCYJ":
                arr[p[1]-1] += p[2]
            elif p[0] == "KECZAP":
                r = 0
                for d in range(p[1]-1, p[2]):
                    if arr[d] % p[3] == 0:
                        r += 1
                result.append(r)
        return result

    def save_test(self, file, test):
        file.write("{}\n".format(self.n))
        file.write(" ".join(str(x) for x in test))

    def save_result(self, file, result):
        file.write(str(result))


if __name__ == "__main__":
    tester = KetchupTest()
    tester.main()#os.getcwd())
