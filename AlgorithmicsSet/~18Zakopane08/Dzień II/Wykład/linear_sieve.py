import os, math

def linear_sieve(N):
    is_composite = [False for _ in range(N+1)]
    primes = []
    for i in range(2, N+1):
        if not is_composite[i]:
            primes.append(i)
        for prime in primes:
            if prime * i <= N:
                is_composite[prime * i] = True
            if i % prime == 0 or prime * i > N:
                break
    return primes
    
def euler_totient(N):
    is_composite = [False for _ in range(N+1)]
    phi = [0 for _ in range(N+1)]
    primes = []
    for i in range(2, N+1):
        if not is_composite[i]:
            primes.append(i)
            phi[i] = i - 1;
        for prime in primes:
            if prime * i <= N:
                is_composite[prime * i] = True
            else:
                break
            if i % prime == 0:
                phi[i * prime] = phi[i] * prime
                break
            else:
                phi[i * prime] = phi[i] * phi[prime]
    return phi
    
def euler_totient_brute(N):
    phi = []
    for i in range(N+1):
        phi.append(0)
        for j in range(i):
            if math.gcd(i, j) == 1:
                phi[-1] += 1
    return phi

'''
def any_multiplicative(N, func_for_prime):
    is_composite = [False for _ in range(N+1)]
    func = [0 for _ in range(N+1)]
    cnt = [0 for _ in range(N+1)]
    primes = []
    for i in range(2, N+1):
        if not is_composite[i]:
            primes.append(i)
            func[i] = func_for_prime(i); cnt[i] = 1
        for prime in primes:
            if prime * i > N:
                break
            is_composite[prime * i] = True
            if i % prime == 0:
                func[i * prime] = func[i] // cnt[i] * (cnt[i] + 1)
                cnt[i * prime] = cnt[i] + 1
                break
            else:
                func[i * prime] = func[i] * func[prime]
                cnt[i * prime] = 1
    return func 
'''   
   
print(linear_sieve(40))
print(euler_totient(20))
print(euler_totient_brute(20))
print(any_multiplicative(20, lambda p: p - 1)) # ?

os.system("pause")