import io, random
from gamma import TestFramework, call_with_io

COMMAND = r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-delta" \
          r"\AlgorithmicsSet\~Ungrouped\Haker\brute\haker-brute.exe"

class HackerTest(TestFramework):
    save_test = True
    self_test = True

    filename_pattern = "tests/testa{i}.{ext}"
    iterable = range(100)
    n = 250
    a = (1, 100)

    def generate_test(self):
        return [random.randint(*self.a) for _ in range(self.n)]
    
    def run_self_test(self, test):
        stream = io.StringIO()
        self.save_test(stream, test)
        result = call_with_io(COMMAND, stream.getvalue())
        return int(result)
    
    def save_test(self, file, test):
        file.write(f"{self.n}\n")
        file.write(" ".join(str(x) for x in test))

    def save_result(self, file, result):
        file.write(str(result))

if __name__ == "__main__":
    tester = HackerTest()
    tester.main()