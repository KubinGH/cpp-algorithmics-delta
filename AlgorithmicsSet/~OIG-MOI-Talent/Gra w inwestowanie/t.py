import random
import gamma

class InvestingGameTester(gamma.TestFramework):
    save_tests = True
    self_test = True

    filename_pattern = "tests/teste{i}.{ext}"
    iterable = range(512)
    external_self_test = "gra-n2.exe"

    N = (1, 1024); K = (0, 1024)

    def generate_test(self, N=N, K=K):
        return (random.randint(*N), random.randint(*K))

    def run_self_test(self, test):
        return int(self.run_external_self_test(test))

    def save_result(self, file, result):
        file.write(str(result))

    def save_test(self, file, test):
        file.write(f"{test[0]} {test[1]}")

if __name__ == "__main__":
    tester = InvestingGameTester()
    tester.main()
