// Miller-Rabin prime test and Rho-Pollard factorization.

// Last revision: Middle of 2018.

#pragma once

#include <algorithm>
#include <iostream>
#include <ext/numeric>
#include <cassert>
#include <list>
#define gcd __gcd

using namespace std;
using __gnu_cxx::power;

template<typename T>
struct mod_multiplies : multiplies<T>
{
    T m; mod_multiplies(T _m) : m(_m) {}
    T operator()(T a, T b) const { return (a*b) % m; }
};
template<>
struct mod_multiplies<uint64_t> : multiplies<uint64_t>
{
    uint64_t m; mod_multiplies(uint64_t _m) : m(_m) {}
    uint64_t operator()(uint64_t a, uint64_t b) const
    {
        if(a>=m) a %= m; if(b>=m) b %= m;
        uint64_t c = (long double)(a) * b / m;
        int64_t r = a * b - c * m;
        return r < 0 ? r%m + m : r%m;
    }
};


// 0: 2^32 - {2, 7, 61} (3)
// 1: 3.8 * 10^18 - {2, 3, 5, 7, 11, 13, 17, 19, 23} (9)
// 2: 2^64 - {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37} (12)
const vector<uint64_t> MR_PRIMES[3] = {
    {2, 7, 61},
    {2, 3, 5, 7, 11, 13, 17, 19, 23},
    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
};
bool miller_rabin_isprime(uint64_t n, const vector<uint64_t>& W)
{
    if(n <= 1) return false; if(n <= 3) return true;
    if(n % 2 == 0) return false;
    mod_multiplies<uint64_t> M(n);
    uint64_t d = n - 1;
    uint32_t r = 0;
    while(d % 2 == 0) d /= 2, r++;
    for(uint64_t a : W)
    {
        if(a + 2 > n)
            continue;
        uint64_t x = power(a, d, M);
        if(x == 1 or x == n - 1)
            continue;
        bool comp = true;
        for(uint32_t i = 0; i < r - 1; i++)
        {
            x = M(x, x);
            if(x == 1)
                return false;
            if(x == n - 1)
            {
                comp = false;
                break;
            }
        }
        if(comp)
            return false;
    }
    return true;
}
bool miller_rabin_isprime(uint64_t n)
{
    if(n < (1llu << 32))
        return miller_rabin_isprime(n, MR_PRIMES[0]);
    else if(n < ((1llu<<61)+(1llu<<60)+(1llu<<59)-(1llu<<58)))
        return miller_rabin_isprime(n, MR_PRIMES[1]);
    else
        return miller_rabin_isprime(n, MR_PRIMES[2]);
}

template<typename T>
bool sqrt_isprime(T n)
{
    if(n <= 1) return false; if(n <= 3) return true;
    for(T i = 2; i * i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}


uint64_t rho_pollard_get_factor(uint64_t n)
{
    if(n % 2 == 0)
        return 2;
    if(miller_rabin_isprime(n))
        return n;
    mod_multiplies<uint64_t> M(n);
    for(uint64_t c = 1; true; c++)
    {
        uint64_t x = 2, y = 2, d = 1;
        while(d == 1)
        {
            x = (M(x, x) + c) % n;
            y = (M(y, y) + c) % n; y = (M(y, y) + c) % n;
            d = gcd(x>y ? x-y : y-x, n);
        }
        if(d != n)
            return d;
    }
    return 1;
}

list<uint64_t> rho_pollard_factorize(uint64_t n)
{
    if(n == 1)
        return {};
    uint64_t d = rho_pollard_get_factor(n);
    list<uint64_t> result;
    if(miller_rabin_isprime(d))
        result.merge({d});
    else
        result.merge(rho_pollard_factorize(d));
    if(miller_rabin_isprime(n/d))
        result.merge({n/d});
    else
        result.merge(rho_pollard_factorize(n/d));
    return result;
}

uint32_t pi_prime_count(uint64_t n)
{
    uint32_t r = 0;
    for(uint64_t i = 2; i <= n; i++)
        r += miller_rabin_isprime(i);
    return r;
}

#undef gcd

int main()
{
    cout << pi_prime_count((1 << 23));
}
