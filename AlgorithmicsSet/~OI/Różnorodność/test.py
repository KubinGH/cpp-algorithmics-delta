import os, traceback

def roz(A, k):
    dmax = dsum = 0
    for i in range(len(A) - k + 1):
        for j in range(len(A[i]) - k + 1):
            fragment = set()
            #print((i, i+k), (j, j+k))
            for y in range(i, i+k):
                for x in range(j, j+k):
                    fragment.add(A[y][x])
            #print(fragment)
            dsum += len(fragment)
            dmax = max(len(fragment), dmax)
    return dmax, dsum

def run_with_stdin():
    m, n, k = [int(x) for x in input().split()]
    A = [[int(x) for x in input().split()] for _ in range(m)]
    print(A)
    dmax, dsum = roz(A, k)
    print(dmax, dsum)

class Tests:
    ocen2 = (
        [[x + y for x in range(100)] for y in range(20)],
        10
    )
    ocen3 = (
        [[x for x in range(1000)]],
        1
    )
    ocen4 = (
        [[x + (200*y) + 10**5 for x in range(200)] for y in range(200)],
        200
    )
    ocen5 = (
        [[x + y for x in range(3000)] for y in range(3000)],
        1000
    )

    @staticmethod
    def run(test):
        dmax, dsum = roz(*test)
        print(dmax, dsum)


def main():
    print("\n".join(" ".join(str(e) for e in row) for row in Tests.ocen5[0]), file=open("out.txt", "w"))
    #Tests.run(Tests.ocen5)

try:
    main()
except:
    traceback.print_exc()
