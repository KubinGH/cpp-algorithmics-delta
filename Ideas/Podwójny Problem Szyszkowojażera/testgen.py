import random
import io

import gamma

class PPSTestFramework(gamma.TestFramework):
    save_tests = True
    self_test = True
    
    filename_pattern = "tests/testg{i}.{ext}"
    iterable = range(10)

    brute_path = r"C:\Users\Admin\Desktop\Pomysły na Zadanka\Podwójny problem szyszkowojażera\model\pps-brute.exe"
    model_path = r"C:\Users\Admin\Desktop\Pomysły na Zadanka\Podwójny problem szyszkowojażera\model\pps.exe"

    n = 16
    bounds = (-1000, 1000)
    def generate_test(self, n=n, bounds=bounds):
        return [(random.randint(*bounds), random.randint(*bounds)) for _ in range(n)]
    
    def run_self_test(self, test):
        stream = io.StringIO()
        self.save_test(stream, test)
        n = len(test)
        out = gamma.call_with_io(self.brute_path if n <= 8 else self.model_path, stream.getvalue())
        return out.strip()

    def save_test(self, file, test):
        file.write(f"{len(test)}\n")
        file.write("\n".join(f"{u} {v}" for u, v in test))

    def save_result(self, file, result):
        file.write(f"{result}\n")
    
if __name__ == "__main__":
    fw = PPSTestFramework()
    fw.main()