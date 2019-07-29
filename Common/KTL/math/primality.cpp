// Miller Rabin primality test.
// Bases in is_prime taken from http://miller-rabin.appspot.com/ - those should be pretty good.
// Complexity: O(log n) per witness.
// miller_rabin_witness - returns true if n = 2^r * d is a probable prime with witness a
// miller_rabin_test - returns true if n is a prime with witnesses W
// is_prime - preferable method for checking primality
// miller_rabin_witness and miller_rabin_test are internals and probably shouldn't
// be used explicitly.
// Last revision: Beginning of 2019

#pragma once

#include <ext/numeric>
#include <cstddef>
#include <vector>
#include "../util/gcc_bit_ext.cpp"
#include "mod_multiplies.cpp"
#include "linear_sieve.cpp"

using std::size_t; using std::uintmax_t;
using std::vector;
using __gnu_cxx::power;

constexpr size_t SMALL_PRIMES_LIMIT = 1 << 10;
const auto __prime_cache_small = linear_sieve(SMALL_PRIMES_LIMIT);

template<typename T>
bool miller_rabin_compositeness_witness(T n, T d, size_t r, T a)
{
    mod_multiplies<T> Zn(n);
    T x = power(a, d, Zn);
    if(x == 1 or x == n - 1)
        return true;
    for(size_t i = 1; i < r; i++)
    {
        x = Zn(x, x);
        if(x == n - 1)
            return true;
    }
    return false;
}

template<typename T>
bool miller_rabin_test(T n, const vector<uintmax_t>& W)
{
    if(n <= 1) return false;
    else if(n <= 3) return true;
    else if(n % 2 == 0) return false;
    size_t r = ctz(n - 1);
    T d = (n - 1) >> r;
    for(auto a1 : W)
    {
        T a = a1 % n;
        if(not a)
            continue;
        if(not miller_rabin_compositeness_witness(n, d, r, a))
            return false;
    }
    return true;
}


bool is_prime(uint32_t n)
{
    if(n < SMALL_PRIMES_LIMIT)
        return n == 2 or n == 3 or n == 5 or binary_search(__prime_cache_small.begin(), __prime_cache_small.end(), (size_t)n);
    else if(n < 341531)
        return miller_rabin_test(n, {9345883071009581737ull});
    else if(n < 1050535501)
        return miller_rabin_test(n, {336781006125ull, 9639812373923155ull});
    else
        return miller_rabin_test(n, {2, 7, 61});
}

bool is_prime(uint64_t n)
{
    if(n < ((uint64_t)1 << 31))
        return is_prime((uint32_t)n);
    else if(n < 55245642489451ull)
        return miller_rabin_test(n, {2, 141889084524735ull, 1199124725622454117ull, 11096072698276303650ull});
    else
        return miller_rabin_test(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}
