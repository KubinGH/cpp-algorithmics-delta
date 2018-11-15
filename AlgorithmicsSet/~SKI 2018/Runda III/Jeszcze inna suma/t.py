from gamma import TestFramework
import random


class SumTester(TestFramework):
    save_tests = True
    self_test = True

    filename_pattern = "tests/testo{i}.{ext}"
    iterable = range(8)

    external_self_test = "sum-q.exe"

    N = 2000
    A = (1, 10**8)

    def generate_test(self, N=N, A=A):
        return [random.randint(*A) for _ in range(N)]

    def save_test(self, file, test):
        file.write(str(len(test)) + "\n")
        file.write(f"{' '.join(str(t) for t in test)}")

    def save_result(self, file, result):
        file.write(result)

    def run_self_test(self, test):
        return self.run_external_self_test(test)

if __name__ == "__main__":
    tester = SumTester()
    tester.main()
