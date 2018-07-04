from random import randint
import io
from gamma import TestFramework, call_with_io

class GridTester(TestFramework):
    save_tests = True
    self_test = True
    brute_path = r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-delta\AlgorithmicsSet\~Solve\Kratka kontratakuje\kratka0.exe"
    filename_pattern = "tests/test{i}.{ext}"
    iterable = range(256)

    w_bounds, h_bounds, a_bounds = (3, 15), (3, 15), (1, 1000)
    def generate_test(self, wb=w_bounds, hb=h_bounds, ab=a_bounds):
        w, h = randint(*wb), randint(*hb)
        return [[randint(*ab) for _ in range(w)] for _ in range(h)]

    def run_self_test(self, test):
        stream = io.StringIO()
        self.save_test(stream, test)
        return int(call_with_io(self.brute_path, stream.getvalue()))
    
    def save_test(self, file, test):
        w, h = len(test[0]), len(test)
        file.write(f"{len(test)} {len(test[0])}\n")
        for row in test:
            file.write(" ".join(str(x) for x in row) + "\n")

    def save_result(self, file, result):
        file.write(str(result))

if __name__ == "__main__":
    tester = GridTester()
    tester.main()
