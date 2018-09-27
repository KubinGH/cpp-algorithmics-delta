import random
import gamma

class IncendioTester(gamma.TestFramework):
    save_tests = True
    self_test = True

    filename_pattern = "tests/testo{i}.{ext}"
    iterable = range(64)
    external_self_test = "incendio-brute.exe"

    N = (4, 64); M = (0, 64)

    def generate_test(self, N=N, M=M):
        n = random.randint(*N)
        m = random.randint(M[0], min(M[1], n**2 - 4))
        return (n, m, random.sample([(i, j) for i in range(n) for j in range(n)], m))

    def run_self_test(self, test):
        return int(self.run_external_self_test(test))

    def save_result(self, file, result):
        file.write(str(result))

    def save_test(self, file, test):
        nl = '\n'
        file.write(f"{test[0]} {test[1]}\n{nl.join(str(x) + ' ' + str(y) for x, y in test[2])}")

if __name__ == "__main__":
    tester = IncendioTester()
    tester.main()
