// Miller Rabin primality test.
// Complexity: 12 runs with O(log n) complexity each.

// Last revision: Beginning of 2019

#pragma once

#include <ext/numeric>
#include <cstddef>
#include <vector>

#include "linear_sieve.cpp"
#include "mod_multiplies.cpp"

using std::uint64_t;
using __gnu_cxx::power;

const auto __prime_cache_12 = linear_sieve(38);

bool miller_rabin_isprime(uint64_t n, const vector<size_t>& W)
{
    if(n <= 1) return false; if(n <= 3) return true;
    if(n % 2 == 0) return false;
    mod_multiplies M(n);
    uint64_t d = n - 1;
    size_t r = 0;
    while(d % 2 == 0) d /= 2, r++;
    for(uint64_t a : W)
    {
        if(a + 2 > n)
            continue;
        uint64_t x = power(a, d, M);
        if(x == 1 or x == n - 1)
            continue;
        for(size_t i = 1; i < r; i++)
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
