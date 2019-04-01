import gamma
import random

class CarelessTester(gamma.TestFramework):
    save_tests = True

    i_transform = lambda cls, i: 192+i
    filename_pattern = "tests-own-di/testx{i}.{ext}"
    iterable = range(64)
    A = "AT"
    N = (4, 10**6)
    def generate_test(self, N=N, A=A):
        return "".join(random.choice(A) for _ in range(random.randint(*N))) + "\n" + \
               "".join(random.choice(A) for _ in range(random.randint(*N)))
    def save_test(self, file, test):
        file.write(test)

if __name__ == "__main__":
    #import os, glob
    #for fin in glob.glob("tests-own-di/*.in"):
    #    fout = fin[:-3] + ".out"
    #    if not os.path.exists(fout):
    #        open(fout, "w")
    tester = CarelessTester()
    tester.main()