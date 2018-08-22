n = 8
M = (1 << n) - 1
B = 0b11010100

def f(B):
	return ((B << 1) ^ (B >> 1)) & M
# f(f(B)) == f2(B)
def f2(B):
	return ((B << 2) ^ (B&1) ^ (B&(1<<7)) ^ (B >> 2)) & M
# f(f(f(f(B)))) == f2(f2(B)) == f4(B)
def fk(B, k):
    if k == 0:
        return B
    elif k == 1:
        return ((B << 1) ^ (B >> 1)) & M
    else:
        return fk(fk(B, k - 1), k - 1)