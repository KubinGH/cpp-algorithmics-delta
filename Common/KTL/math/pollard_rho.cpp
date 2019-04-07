// Pollard's rho algorithm for finding factors.
// Complexity: O(log n + n ^ 0.25)
// Note: use the factorize_int function for actual factorization.
// Since it checks primes up to L = BRUTE_FACTOR_LIMIT before running
// Pollard's rho, at most log_L(n) runs will be executed.
// This should make the routine significantly faster.

// Last revision: March 2019

#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>
#include <list>

#include "linear_sieve.cpp"
#include "mod_multiplies.cpp"
#include "miller_rabin.cpp"

using std::multiplies;
using std::vector; using std::list;
using std::__lg; using std::__gcd;
using std::uint64_t;

constexpr size_t BRUTE_FACTOR_LIMIT = 1 << 16;

uint64_t rho_pollard_get_factor(uint64_t n)
{
    if(n % 2 == 0)
        return 2;
    if(miller_rabin_isprime(n))
        return n;
    mod_multiplies M(n);
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
    if(n == d)
        return {n};
    list<uint64_t> result;
    result.merge(rho_pollard_factorize(d));
    result.merge(rho_pollard_factorize(n/d));
    return result;
}

const auto __prime_cache_fact = linear_sieve(BRUTE_FACTOR_LIMIT);

list<uint64_t> factorize_int(uint64_t n)
{
    list<uint64_t> result;
    for(auto p : __prime_cache_fact)
        while(n % p == 0)
            n /= p, result.push_back(p);
    result.merge(rho_pollard_factorize(n));
    return result;
}
