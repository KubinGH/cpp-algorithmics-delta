# Used in XVI OI 'ROB'

def R(A=(1, 32), B=(1, 16)):
    for a in range(*A):
        for b in range(*B):
            if b == 0: continue
            for c in range(a, A[1]):
                r = 0
                for i in range(a, c+1):
                    if i%b == 0:
                        r += 1
                assert r == F(a, b, c), (a, b, c, r, F(a, b, c))

def F(a, b, c):
    if b < 0: a, b, c = -c, -b, -a
    return (c - c%b)//b - (a + (b-a%b)%b)//b + 1