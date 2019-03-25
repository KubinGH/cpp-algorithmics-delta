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

def left_cnt2(n):
    if n == 0: return 0
    if n == 1: return 1
    if n == 2 or n == 3: return 2
    if has_on_left(n):
        return 2**lg(n-1) - (n - 2**(lg(n))) + 1
    else:
        return left_cnt(n)

def right_cnt2(n):
    return sum(has_on_right(i) for i in range(1, n+1))
def center_cnt2(n):
    return lg(n) + 1

def sks(n):
    return left_cnt(n) + right_cnt(n) - center_cnt(n)

for i in range(1, 32):
    print(i, left_cnt2(i), right_cnt2(i), center_cnt2(i))
    print(i, left_cnt(i), right_cnt(i), center_cnt(i), sks(i))
    #assert left_cnt(i) == left_cnt2(i)
    #assert right_cnt(i) == right_cnt2(i)
    #assert center_cnt(i) == center_cnt2(i)
