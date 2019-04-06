// Miller-Rabin prime test and Rho-Pollard factorization.
// Also includes a linear sieve, faster modular multiplication
// by approximation and a factorization utility function.

// Last revision: March 2019.

#pragma once

#include <ext/numeric>
#include <functional>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdint>
#include <vector>
#include <list>

using std::multiplies;
using std::vector; using std::list;
using std::__lg; using std::__gcd;
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
        return r < 0 ? r%(int64_t)m + m : r%(int64_t)m;
    }
};

vector<uint32_t> linear_sieve(size_t n)
{
    vector<uint32_t> P, M(n);
    P.reserve(2 * n / __lg(n));
    for(uint32_t x = 2; x < n; x++)
    {
        if(not M[x])
            M[x] = x, P.push_back(x);
        for(size_t i = 0; i < P.size() and x * P[i] < n and P[i] <= M[x]; i++)
            M[x * P[i]] = P[i];
    }
    return P;
}

const auto __prime_cache_b16 = linear_sieve(1 << 16);
const auto __prime_cache_12 = linear_sieve(38);

bool miller_rabin_isprime(uint64_t n, const vector<uint32_t>& W)
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
        for(uint32_t i = 0; i < r - 1; i++)
        {
            x = M(x, x);
            if(x == n - 1)
                goto next_witness;
        }
        return false;
    next_witness:;
    }
    return true;
}
bool miller_rabin_isprime(uint64_t n)
{
    return miller_rabin_isprime(n, __prime_cache_12);
}

uint64_t rho_pollard_get_factor(uint64_t n)
{
    if(n % 2 == 0)
        return 2;
    if(miller_rabin_isprime(n))
        return n;
    mod_multiplies<uint64_t> M(n);
    for(uint64_t c = 3; true; c++)
    {
        uint64_t x = 2, y = 2, d = 1;
        while(d == 1)
        {
            x = (M(x, x) + c) % n;
            y = (M(y, y) + c) % n; y = (M(y, y) + c) % n;
            d = __gcd(x>y ? x-y : y-x, n);
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

list<uint64_t> factorize_int(uint64_t n)
{
    list<uint64_t> result;
    for(auto p : __prime_cache_b16)
        while(n % p == 0)
            n /= p, result.push_back(p);
    result.merge(rho_pollard_factorize(n));
    return result;
}
