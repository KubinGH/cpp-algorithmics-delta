// Miller Rabin primality test.
// Complexity: 12 (64bit) or 3 (32bit) runs with O(log n) complexity each.

// Last revision: Beginning of 2019

#pragma once

#include <ext/numeric>
#include <cstddef>
#include <vector>

#include "linear_sieve.cpp"
#include "mod_multiplies.cpp"

using std::size_t;
using __gnu_cxx::power;

const vector<size_t> MILLER_RABIN_WITNESSES_32 = {2, 7, 61};
const vector<size_t> MILLER_RABIN_WITNESSES_64 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

template<typename T>
bool miller_rabin_isprime(T n, const vector<size_t>& W)
{
    if(n <= 1 or n % 2 == 0) return false;
    if(n <= 3) return true;
    mod_multiplies<T> M(n);
    T d = n - 1;
    size_t r = 0;
    while(d % 2 == 0) d /= 2, r++;
    for(auto a : W)
    {
        if(a + 2 > n)
            continue;
        T x = power(a, d, M);
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
template<typename T>
bool miller_rabin_isprime(T n);

template<>
bool miller_rabin_isprime<uint64_t>(uint64_t n)
{
    return miller_rabin_isprime(n, MILLER_RABIN_WITNESSES_64);
}
template<>
bool miller_rabin_isprime<uint32_t>(uint32_t n)
{
    return miller_rabin_isprime(n, MILLER_RABIN_WITNESSES_32);
}
