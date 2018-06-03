import random
import io

import gamma

class BitsTestFramework(gamma.TestFramework):
    save_tests = True
    self_test = True
    
    filename_pattern = "tests/teste{i}.{ext}"
    iterable = range(2)

    brute_path = r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-delta\Ideas\Bity\model\bity-brute.exe"
    model_path = r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-delta\Ideas\Bity\model\bity.exe"

    n = 10**5
    q = 5*10**5
    bounds = (0, 2**8 - 1)
    def generate_test(self, n=n, q=q, bounds=bounds):
        elements = [random.randint(*bounds) for _ in range(n)]
        queries = []
        for i in range(q):
            c, a, b = random.choice("^&|?"), random.randint(0, n-1), random.randint(0, n-1)
            a, b = random.randint(1, 6), n - 1 - random.randint(1, 6)
            if c in "^&|":
                queries.append((c, a, b, random.randint(*bounds)))
            else:
                queries.append((c, a, b))
        return [elements, queries]
    
    def run_self_test(self, test):
        stream = io.StringIO()
        self.save_test(stream, test)
        n, q = len(test[0]), len(test[1])
        out = gamma.call_with_io(self.brute_path if False else self.model_path, stream.getvalue())
        return [int(x) for x in out.split("\n") if x]

    def save_test(self, file, test, _nl="\n"):
        file.write(f"{len(test[0])} {len(test[1])}\n")
        file.write(f"{' '.join(str(x) for x in test[0])}\n")
        file.write(f"{_nl.join(' '.join(str(x) for x in q) for q in test[1])}\n")
        
    def save_result(self, file, result, _nl="\n"):
        file.write(f"{_nl.join(str(x) for x in result)}\n")
    
if __name__ == "__main__":
    fw = BitsTestFramework()
    fw.main()