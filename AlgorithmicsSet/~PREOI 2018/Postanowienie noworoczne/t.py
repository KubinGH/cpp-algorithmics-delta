import random

import sys
sys.path.append(r"C:\Program Files\AddToPath")
from gamma import TestFramework

class PostanowienieTester(TestFramework):
    save_tests = False
    self_test = True
    iterable = range(5)
    n = 5
    k = None
    def generate_test(self, n=n, k=k):
        if k is None: k = random.randint(0, 4*n)
                
