import random
import itertools
import functools
import io

from gamma import TestFramework, call_with_io

COMMAND = r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-"\
          r"delta\AlgorithmicsSet\~OIG-MOI\Spacer\brute\spacer-"\
          r"brute.exe"

class SpacerTester(TestFramework):
    save_tests = True
    self_test = True
    iterable = range(240)
    filename_pattern = "tests/testd{i}.{ext}"

    n = 5000
    x_bounds = (-500, 500)
    y_bounds = (0, 500)
    def generate_test(self):
        return [(random.randint(*self.x_bounds), 
                 random.randint(*self.y_bounds)) 
                for _ in range(self.n)]

    def run_self_test(self, test, n=n):
        stream = io.StringIO()
        self.save_test(stream, test)
        return int(call_with_io(COMMAND, stream.getvalue()))

    def save_test(self, file, test):
        file.write(f"{self.n}\n")
        file.write("\n".join(f"{x} {y}" for x, y in test))

    def save_result(self, file, result):
        file.write(str(result))


if __name__ == "__main__":
    tester = SpacerTester()
    tester.main()
