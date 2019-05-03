import operator
import traceback

def fast_power(a, n, identity=None, func=operator.mul):
    if n < 0:
        return fast_power(~a, -n, identity, func)
    if n and identity is None:
        n -= 1; r = a
    else:
        r = identity
    while n:
        if n % 2: r = func(r, a)
        a = func(a, a)
        n //= 2
    return r

# Fast Fibonacci Transform
def FFT(x, y, f0, f1, mod=0):
    # f(n+1) = x f(n) + y f(n-1)
    class FFTPair:
        def __init__(self, A, B): self.A, self.B = A, B
        def __repr__(self): return f"FFTPair({self.A}, {self.B})"
        if mod == 0:
            def __mul__(self, other):
                A, B, C, D = self.A, self.B, other.A, other.B
                return FFTPair(A*D + B*C + x*A*C, B*D + y*A*C)
        else:
            def __mul__(self, other):
                A, B, C, D = self.A, self.B, other.A, other.B
                return FFTPair((A*D + B*C + x*A*C)%mod, (B*D + y*A*C)%mod)
        def __invert__(self):
            A, B = self.A, self.B
            Q = B**2 + x*A*B - y*A**2
            At = -A//Q if abs(-A%Q) <= 10**-7 else -A/Q
            Bt = (x*A + B)//Q if abs((x*A + B)%Q) <= 10**-7 else (x*A + B)/Q
            print(f"~{self} = {FFTPair(At, Bt)}")
            return FFTPair(At, Bt)
    identity = FFTPair(0, 1)
    def f(n):
        if n == 0: return f0
        return (FFTPair(f1, y*f0) * fast_power(FFTPair(1, 0), n-1, identity)).A
    return f


# In short:
"""
FFT(x, y, f0, f1): # f(n+1) = x f(n) + y f(n-1)
let (A, B) * (C, D) = (AD + BC + xAC, BD + yAC)
# (f1, y f0) * (1, 0)^n  = (f(n+1), y f(n))
"""
