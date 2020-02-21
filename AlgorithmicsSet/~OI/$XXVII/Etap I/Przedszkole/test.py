import random, os, subprocess, functools, operator, math
from string import ascii_lowercase

MOD = 10**9 + 7

def fallfactorial(n, k):
    return math.factorial(n) // math.factorial(n-k) if n >= k else 0

def prob(p):
    return random.random() <= p

def range_sample(r, k):
    A = []; A1 = set()
    for i in range(k):
        x = random.randrange(r.start, r.stop, r.step)
        while x in A1:
            x = random.randrange(r.start, r.stop, r.step)
        A1.add(x)
        A.append(x)
    return A

def product(it):
    return functools.reduce(lambda a, b: a*b % MOD, it, 1)

def reenumerate_nodes(edges, re):
    return [(re[u], re[v]) for u, v in edges]

def graph_shuffle(n, edges):
    re = list(range(n))
    random.shuffle(re)
    return [random.choice(((u, v), (v, u))) for u, v in reenumerate_nodes(edges, re)]


def random_tree(n):
    edges = []
    for i in range(n - 1):
        edges.append((random.randint(0, i), i+1))
    return n, edges, lambda z: z * pow(z - 1, n - 1, MOD) % MOD

def complete_graph(n):
    edges = [(u, v) for u in range(n) for v in range(u+1, n)]
    return n, edges, lambda z: fallfactorial(z, n) % MOD

def barbell_graph(n):
    n, edges1, calc = complete_graph(n)
    edges2 = reenumerate_nodes(edges1, list(range(n, 2*n)))
    edges = edges1 + edges2 + [(random.randint(0, n-1), random.randint(n, 2*n-1))]
    return 2*n, edges, lambda z: fallfactorial(z-1, n-1)%MOD * fallfactorial(z, n)%MOD * (z-1) % MOD

def centipede_graph(n):
    edges = []
    for i in range(n - 1):
        edges.append((i, i+1))
    for i in range(n):
        edges.append((i, i+n))
    return 2*n, edges, lambda z: z * pow(z-1, 2*n-1, MOD) % MOD

def cycle_graph(n):
    edges = []
    for i in range(n-1):
        edges.append((i, i+1))
    edges.append((0, n-1))
    return n, edges, lambda z: (pow(-1, n, MOD)*(z - 1) + pow(z-1, n, MOD)) % MOD

def wheel_graph(n):
    edges = []
    for i in range(n-1):
        edges.append((i, i+1))
    edges.append((0, n-1))
    for i in range(n):
        edges.append((i, n))
    return n+1, edges, lambda z: z*(pow(z-2, n, MOD) - pow(-1, n+1, MOD)*(z - 2)) % MOD

def random_graph(n, m):
    all_edges = complete_graph(n)[1]
    edges = random.sample(all_edges, m)
    return n, edges, lambda z: int(call_with_io("./przb", str(Test(n, edges, None, [z]))))


def chain_graphs(parts):
    edges = []
    n = 0
    F = []
    for m, e, f in parts:
        edges += reenumerate_nodes(e, list(range(n, n+m)))
        n += m
        F.append(f)
    edges = graph_shuffle(n, edges)
    return n, edges, lambda z: product(f(z) for f in F)

def iotacycles(n):
    i = 2
    s = 0
    while s <= n:
        s += i
        i += 1
    return chain_graphs(cycle_graph(j) for j in range(3, i))

def random_small_queries():
    return list(range(1, 8))

query_per_log = 3
def random_queries(LOG2=30):
    q = []
    for lg in range(LOG2):
        for i in range(query_per_log):
            q.append(min(random.randint(2**lg, 2*2**lg-1), 10**9))
    q += random_small_queries()
    random.shuffle(q)
    return q

class Test:
    def __init__(self, n, edges, calc, queries):
        self.n, self.edges, self.calc, self.queries = n, edges, calc, queries

    def __str__(self):
        return f"{self.n} {len(self.edges)} {len(self.queries)}" + ("\n" if self.edges else "")\
            + "\n".join(f"{u+1} {v+1}" for u, v in self.edges) + ("\n" if self.queries else "") \
            + "\n".join(str(k) for k in self.queries)

    @classmethod
    def from_parts(cls, parts, k=30):
        return cls(*chain_graphs(parts), random_queries(k))

    @classmethod
    def trees(cls, n, c):
        return cls.from_parts((random_tree(random.randint(1, n)) for _ in range(c)), 30)

    @classmethod
    def complete(cls, n, c):
        return cls.from_parts((complete_graph(random.randint(1, n)) for _ in range(c)), 16)

    @classmethod
    def barbell(cls, n, c):
        return cls.from_parts((barbell_graph(random.randint(1, n)) for _ in range(c)), 16)

    @classmethod
    def centipedes(cls, n, c):
        return cls.from_parts((centipede_graph(random.randint(1, n)) for _ in range(c)), 30)

    @classmethod
    def cycles(cls, n, c):
        return cls.from_parts((cycle_graph(random.randint(3, n)) for _ in range(c)), 30)

    @classmethod
    def wheels(cls, n, c):
        return cls.from_parts((wheel_graph(random.randint(4, n)) for _ in range(c)), 30)

    @classmethod
    def random(cls, n, m):
        return cls(*random_graph(n, m), random_queries(2))

    @classmethod
    def iotacycles(cls, n, c):
        return cls.from_parts((iotacycles(random.randint(3, n)) for _ in range(c)), 30)


def call_with_io(command, string):
    return subprocess.run(
        command, input=string.encode(), capture_output=True,
        timeout=5
    ).stdout.decode()

check_answers = True
testdir = "self"
def test_solution(name, test, desc, code):
    with open(f"{testdir}/in/{name}{code}.in", "w") as f:
        f.write(str(test))
    print(code, desc)
    out = call_with_io(f"./{name}", str(test))
    with open(f"{testdir}/out/{name}{code}.out", "w") as f:
        f.write(out)
    out = out.split()
    for i in range(len(test.queries)):
        print(f"\r{i}", end=" ")
        if check_answers:
            a, b = int(out[i]), test.calc(test.queries[i])
            print(f"\r{i} <{test.queries[i]}> ({a}, {b})", flush=True, end="")
            assert a == b
    print("\rOK" + " "*48, flush=True)


def self():
    global check_answers, testdir, query_per_log
    check_answers, testdir, query_per_log = True, "self", 3
    test_solution("prz", Test.cycles(10**1, 10**4), "cycles", "0a")
    test_solution("prz", Test.cycles(10**1, 10**4), "cycles", "0b")
    test_solution("prz", Test.cycles(10**2, 10**3), "cycles", "0c")
    test_solution("prz", Test.cycles(10**2, 10**3), "cycles", "0d")
    test_solution("prz", Test.cycles(10**3, 10**2), "cycles", "0e")
    test_solution("prz", Test.cycles(10**3, 10**2), "cycles", "0f")
    test_solution("prz", Test.cycles(10**4, 10**1), "cycles", "0g")
    test_solution("prz", Test.cycles(10**4, 10**1), "cycles", "0h")
    test_solution("prz", Test.cycles(10**5, 10**0), "cycles", "0i")
    test_solution("prz", Test.cycles(10**5, 10**0), "cycles", "0j")
    test_solution("prz", Test.iotacycles(10**5, 1), "(iota)cycles", "0k")
    test_solution("prz", Test.iotacycles(10**4, 10), "(iota)cycles", "0l")
    test_solution("prz", Test.iotacycles(10**3, 100), "(iota)cycles", "0m")
    test_solution("prz", Test.trees(25, 5), "trees", "1a")
    test_solution("prz", Test.trees(25, 5), "trees", "1b")
    test_solution("prz", Test.trees(25, 5), "trees", "1c")
    test_solution("prz", Test.complete(15, 5), "complete", "2a")
    test_solution("prz", Test.complete(15, 5), "complete", "2b")
    test_solution("prz", Test.complete(15, 5), "complete", "2c")
    test_solution("prz", Test.barbell(7, 5), "barbell", "3a")
    test_solution("prz", Test.barbell(7, 5), "barbell", "3b")
    test_solution("prz", Test.barbell(7, 5), "barbell", "3c")
    test_solution("prz", Test.centipedes(12, 5), "centipedes", "4a")
    test_solution("prz", Test.centipedes(12, 5), "centipedes", "4b")
    test_solution("prz", Test.centipedes(12, 5), "centipedes", "4c")
    test_solution("prz", Test.from_parts([
        cycle_graph(10), cycle_graph(10), random_tree(5)
    ]), "2cycle+tree", "5a")
    test_solution("prz", Test.from_parts([
        cycle_graph(10), cycle_graph(10), random_tree(5)
    ]), "2cycle+tree", "5b")
    test_solution("prz", Test.from_parts([
        cycle_graph(10), cycle_graph(10), random_tree(5)
    ]), "2cycle+tree", "5c")
    test_solution("prz", Test.wheels(5, 1), "wheels", "6a")
    test_solution("prz", Test.wheels(15, 5), "wheels", "6b")
    test_solution("prz", Test.wheels(15, 5), "wheels", "6c")
    test_solution("prz", Test.wheels(15, 5), "wheels", "6d")

    test_solution("prz", Test.random(8, 8), "random", "9a")
    test_solution("prz", Test.random(8, 8), "random", "9b")
    test_solution("prz", Test.random(8, 8), "random", "9c")
    test_solution("prz", Test.random(8, 8), "random", "9e")
    test_solution("prz", Test.random(8, 8), "random", "9f")
    test_solution("prz", Test.random(8, 8), "random", "9g")
    test_solution("prz", Test.random(8, 8), "random", "9h")
    test_solution("prz", Test.random(8, 8), "random", "9i")
    test_solution("prz", Test.random(8, 8), "random", "9j")

def gen():
    global check_answers, testdir
    check_answers, testdir, query_per_log = False, "tests", 30
    groups = [
        [
            (lambda: Test.cycles(10**1, 10**4), 4), (lambda: Test.cycles(10**2, 10**3), 5),
            (lambda: Test.cycles(10**3, 10**2), 4), (lambda: Test.cycles(10**4, 10**1), 4),
            (lambda: Test.cycles(10**5, 10**0), 4), (lambda: Test.iotacycles(10**5, 1), 2),
            (lambda: Test.iotacycles(10**4, 10), 2), (lambda: Test.iotacycles(10**3, 100), 1)
        ],
        [
            (lambda: Test.trees(25, 1), 5), (lambda: Test.trees(12, 2), 5),
            (lambda: Test.trees(5, 5), 10)
        ],
        [
            (lambda: Test.random(15, random.randint(1, 15*14//2)), 12),
            (lambda: Test.random(15, random.randint(1, 50)), 12)
        ],
        [
            (lambda: Test.random(10**3, 24), 10),
            (lambda: Test.random(100, 24), 10)
        ],
        [
            (lambda: Test.centipedes(5, 2), 5), (lambda: Test.centipedes(10, 1), 5),
            (lambda: Test.from_parts([random_tree(7), random_tree(8), centipede_graph(4)]), 10)
        ],
        [
            (lambda: Test.complete(15, 1), 10), (lambda: Test.complete(5, 3), 5),
            (lambda: Test.barbell(7, 1), 5), (lambda: Test.barbell(3, 2), 5)
        ],
        [
            (lambda: Test.wheels(6, 2), 10), (lambda: Test.wheels(11, 1), 10)
        ],
        [
            (lambda: Test.random(8, 8), 20)
        ]
    ]

    for g, lst in enumerate(groups):
        i = 0
        for t in lst:
            for _ in range(t[1]):
                T = t[0]()
                assert g == 0 or T.n <= 15 or len(T.edges) <= 24
                test_solution("prz", T, "gen", f"{g}{ascii_lowercase[i]}")
                i += 1

subprocess.run(f"rm prz", shell=True)
subprocess.run(f"mkcxxO prz.cpp prz", shell=True)
#gen()
self()
