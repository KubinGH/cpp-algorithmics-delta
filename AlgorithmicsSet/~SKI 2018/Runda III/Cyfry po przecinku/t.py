from gamma import TestFramework
import random

G = 9

class CyfTester(TestFramework):
    save_tests = True
    self_test = True

    i_transform = lambda cls, i: i + (G//3-1)*4
    filename_pattern = "tests/test{i}.{ext}"
    iterable = range(8)

    external_self_test = "cyf.exe"

    Q = 10**5
    B = 10**G

    def generate_test(self, Q=Q, B=B):
        return [[random.randint(a, B) for a in (2, 0, 1, 1)] for _ in range(Q)]

    def save_test(self, file, test):
        file.write(str(len(test)) + "\n")
        for row in test:
            file.write(f"{' '.join(str(t) for t in row)}\n")

    def save_result(self, file, result):
        file.write(result)

    def run_self_test(self, test):
        return self.run_external_self_test(test)

if __name__ == "__main__":
    tester = CyfTester()
    tester.main()
