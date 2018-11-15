from gamma import TestFramework
import random

class AgarTester(TestFramework):
    save_tests = True
    self_test = True

    filename_pattern = "tests/test{i}.{ext}"
    iterable = range(512)

    external_self_test = "agar-brute.exe"

    n = 512
    w = (1, 10**5)

    def generate_test(self, n=n, w=w):
        row = [random.randint(*w) for _ in range(n)]
        k = random.randint(0, n-1)
        row[k] = min(int(row[k]**1.33), 10**9)
        return (n, k, row)

    def save_test(self, file, test):
        file.write(f"{test[0]} {test[1]+1}\n{' '.join(str(x) for x in test[2])}")

    def save_result(self, file, result):
        file.write(result)

    def run_self_test(self, test):
        return self.run_external_self_test(test)

if __name__ == "__main__":
    tester = AgarTester()
    tester.main()
