// Rolling hashes.

// Last revision: Middle of 2018

#pragma once

#include <cstddef>
#include <cstdint>
using std::size_t;
using std::uint64_t;

// Mods: 1e9+7, 1e9+11, 1e9+21, 1e9+33, 2^31 - 1
template<typename T, T MOD, T BASE, size_t N>
struct rolling_hash
{
    T H[N];
    T base_pow[N];
    size_t n;
    template<typename Iterator>
    rolling_hash(Iterator begin, Iterator end, T fix = 0)
    {
        n = distance(begin, end);
        Iterator it = begin;
        for(size_t i = 0; i < n; i++)
        {
            if(i > 0)
                H[i] = H[i-1] * BASE, H[i] %= MOD;
            H[i] += T(*it) + fix;
            H[i] %= MOD;

            if(i > 0)
                base_pow[i] = (base_pow[i-1] * BASE) % MOD;
            else
                base_pow[i] = 1;
            it++;
        }
    }
    const T& operator[] (size_t i) const { return H[i]; }
    T operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - ((H[i-1]*base_pow[j - i + 1]) % MOD)) % MOD;
    }
};

// Mod 2^31 - 1 (should work for any P = 2^K - 1, P is prime)
// the conditional can be deleted for additional speed
template<uint64_t K = 31>
uint64_t mersenne_mod(uint64_t x)
{
    const uint64_t P = (1 << K) - 1;
    x = (x >> K) + (x & P);
    x = (x >> K) + (x & P);
    return x == P ? 0 : x;
}
