from gamma import TestFramework, call_with_io
from random import randint
import io

BRUTE_COMMAND = r"C:\Users\Admin\Desktop\Pomysły na Zadanka\Złota skrzynia\zlo.exe"

class GoldenTester(TestFramework):
    save_tests = True
    self_test = True

    filename_pattern = "tests/zol{i}z.{ext}"
    iterable = range(0)

    size_bounds = (120, 128)
    elem_bounds = (1, 1000)

    def generate_test(self, size_bounds=size_bounds, elem_bounds=elem_bounds):
        w, h, d = (randint(*size_bounds) for _ in range(3))
        k = randint(int(min(w, h, d)*0.75), min(w, h, d))
        return (w, h, d, k, [[[randint(*elem_bounds) for _ in range(w)] 
                              for _ in range(h)] for _ in range(d)])
    
    def run_self_test(self, test):
        stream = io.StringIO(); self.save_test(stream, test)
        return int(call_with_io(BRUTE_COMMAND, stream.getvalue()))

    def save_test(self, file, test):
        w, h, d, k, A = test
        file.write(f"{w} {h} {d} {k}\n")
        for layer in A:
            for row in layer:
                file.write(" ".join(str(x) for x in row) + "\n")
            file.write("\n")
    
    def save_result(self, file, result):
        file.write(str(result))
        
if __name__ == "__main__":
    tester = GoldenTester()
    tester.main()