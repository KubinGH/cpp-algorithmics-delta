def lg(n):
    return n.bit_length() - 1

def has_on_left(n):
    if n <= 1: return bool(n)
    k = lg(n)
    return (n & ((2**k) | (2**(k-1)))) == 2**k
    
def has_on_right(n):
    if n <= 1: return bool(n)
    k = lg(n & -n)
    return (n & ((2**k) | (2**(k+1)))) == 2**k

def has_center(n):
    if n == 0: return False
    return (n & (n-1)) == 0

def left_cnt(n):
    return sum(has_on_left(i) for i in range(1, n+1))
def right_cnt(n):
    return sum(has_on_right(i) for i in range(1, n+1))
def center_cnt(n):
    return sum(has_center(i) for i in range(1, n+1))

def sks(n):
    return left_cnt(n) + right_cnt(n) - center_cnt(n)

k = int(input())
X = [int(x) for x in input().split()]

s = ""
for i, x in enumerate(X):
    s += x * ("1" if i%2 == 0 else "0")
n = int(s, 2)

g = 0
b = "1"
Y = []
for c in bin(sks(n))[2:]:
    if c == b:
        g += 1
    else:
        Y.append(g)
        g = 1
        b = c
Y.append(g)
print(len(Y))
print(" ".join(str(y) for y in Y))
