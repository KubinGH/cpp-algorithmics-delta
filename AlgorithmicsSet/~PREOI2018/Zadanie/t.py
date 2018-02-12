import random

import sys
sys.path.append(r"C:\Program Files\AddToPath")
from gamma import TestFramework

class ZadanieTester(TestFramework):
    save_tests = True
    self_test = True
    iterable = range(1000)
    filename_pattern = "tests/atest{i}.{ext}"
    t = 10
    n = 4
    def generate_test(self, t=t, n=n):
        test = []
        for ti in range(t):
            '''
            s = random.randint(0, 2**(n-1)-1)
            S = self.bitlist(s, n)
            P = self.create_ps_table(S)
            test.append(P)
            '''
            test.append([random.randint(0, 3) for i in range(n)])
        return test

    @staticmethod
    def bitlist(s, n=0):
        return [int(b) for b in bin(s)[2:].zfill(n)]

    @staticmethod
    def create_ps_table(S):        
        P = []
        for i in range(1, len(S)+1):
            for j in range(i-1, -1, -1):
                if S[:j] == S[i-j:i]:
                    P.append(j)
                    break
        return P

    def run_self_test(self, test, t=t, n=n):
        result = []
        for P in test:
            for s in range(0, 2**(len(P)-1)):
                S = self.bitlist(s, len(P))
                P2 = self.create_ps_table(S)
                if P == P2:
                    result.append(S)
                    break
            else:
                result.append(None)
        return result

    def save_test(self, file, test):
        file.write("{}\n".format(self.t))
        for P in test:
            file.write("{}\n".format(len(P)))
            file.write("{}\n".format(" ".join(str(i) for i in P)))

    def save_result(self, file, result):
        for r in result:
            if r is not None:
                file.write("TAK\n{}\n".format("".join("b" if b else "a" for b in r)))
            else:
                file.write("NIE\n")

if __name__ == "__main__":
    tester = ZadanieTester()
    tester.main()
