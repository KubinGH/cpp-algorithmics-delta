import random
import itertools
import functools

import sys
sys.path.append(r"C:\Program Files\AddToPath")
from gamma import TestFramework

def break_points(i, j, k, b=1):
    if k == 0:
        yield ()
    else:
        for x in range(i, j):
            yield from ((x,) + b for b in break_points(x+b, j, k - 1))

class PielgrzymiTester(TestFramework):
    save_tests = True
    iterable = range(50)
    filename_pattern = "tests/testb{i}.{ext}"

    n = 20
    k = 5
    max_w = 50
    def generate_test(self):
        return [random.randint(1, self.max_w) for _ in range(self.n)]

    def run_self_test(self, test, n=n, k=k):
        best = float("inf")
        for points in break_points(2, n-1, k-1, 2):
            points = (0,) + points + (n,)
            sums = [sum(test[a:b]) for a, b in zip(points, points[1:])]
            best = min(best, max(sums))
        print(test, "->", best)
        return best

    def save_test(self, file, test):
        file.write("{} {}\n".format(self.n, self.k))
        file.write(" ".join(str(t) for t in test))

    def save_result(self, file, result):
        file.write(str(result))


if __name__ == "__main__":
    tester = PielgrzymiTester()
    tester.run_self_test([5, 1, 2, 1, 1], 5, 2)
    tester.main()
