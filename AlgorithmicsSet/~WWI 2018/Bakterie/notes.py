n = 8
M = (1 << n) - 1
B = 0b11010100

def f(B):
    return ((B << 1) ^ (B >> 1)) & M
# f(f(B)) == f2(B)
def f2(B):
    return ((B << 2) ^ (B&1) ^ (B&(1<<7)) ^ (B >> 2)) & M

def brute_sim(B, k):
    for i in range(k):
        B = f(B)
    return B
