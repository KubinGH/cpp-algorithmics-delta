import random
import io

import gamma

class FilmTestFramework(gamma.TestFramework):
    save_tests = True
    self_test = True
    
    filename_pattern = "tests/testb{i}.{ext}"
    iterable = range(100)

    exe_path = r"C:\Users\Admin\Documents\GitHub\cpp-algorithmics-delta\AlgorithmicsSet\~WWI 2018\Kwalifikacyjny\Filmy\filmy.exe"

    m = 20
    endtime = 10**4
    d_bounds = (10, 2000)
    c_bounds = (1, 100)

    def generate_test(self, m=m, endtime=endtime, d_bounds=d_bounds, c_bounds=c_bounds):
        test = [endtime]
        start = random.randrange(0, m)
        for i in range(m):
            d = random.randint(*d_bounds)
            this = sorted({random.randint(0, endtime) for _ in range(random.randint(*c_bounds))})
            if i == start:
                this.insert(0, 0)
            test.append((d, this))
        return test
    
    def run_self_test(self, test):
        stream = io.StringIO()
        self.save_test(stream, test)
        out = gamma.call_with_io(self.exe_path, stream.getvalue())
        return int(out.strip())
            
    def save_test(self, file, test, _nl="\n"):
        file.write(f"{len(test)-1} {test[0]}\n")
        for t in test[1:]:
            file.write(f"{t[0]} {len(t[1])} " + " ".join(str(x) for x in t[1]) + "\n")

    def save_result(self, file, result, _nl="\n"):
        file.write(f"{result}\n")
        print(result)

if __name__ == "__main__":
    fw = FilmTestFramework()
    fw.main()