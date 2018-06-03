import random
import io

import gamma

class DnDTestFramework(gamma.TestFramework):
    save_tests = True
    self_test = True
    
    filename_pattern = "tests/teste{i}.{ext}"
    iterable = range(4)

    brute_path = r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-delta\Ideas\Drzewo na drzewie\model\dnd-brute.exe"
    model_path = r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-delta\Ideas\Drzewo na drzewie\model\dnd.exe"

    n = 30000
    def generate_test(self, n=n):
        edges = []
        for v in range(1, n):
            u = random.randint(0, v-1)
            edges.append([u, v])
        return edges
    
    def run_self_test(self, test):
        stream = io.StringIO()
        self.save_test(stream, test)
        n = len(test)
        out = gamma.call_with_io(self.brute_path if n <= 3 else self.model_path, stream.getvalue())
        return int(out.strip())
            
    def save_test(self, file, test, _nl="\n"):
        file.write(f"{len(test)+1}\n")
        file.write("\n".join(f"{u} {v}" for u, v in test))

    def save_result(self, file, result, _nl="\n"):
        file.write(f"{result}\n")
    
if __name__ == "__main__":
    fw = DnDTestFramework()
    fw.main()