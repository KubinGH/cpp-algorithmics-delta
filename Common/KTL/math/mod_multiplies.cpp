// Modular multiplication of 64-bit integers using the approximation method
// in constant time.
// Will probably fail for numbers larger than ~2^63, but this is enough
// most of the time.

// Last revision: Beginning of 2019

#pragma once

#include <functional>
#include <cstdint>

using std::multiplies; using std::uint64_t; using std::int64_t;

template<typename T>
struct mod_multiplies;

template<>
struct mod_multiplies<uint64_t> : multiplies<uint64_t>
{
    uint64_t m;
    mod_multiplies(uint64_t _m) : m(_m) {}
    uint64_t operator()(uint64_t a, uint64_t b) const
    {
        if(a>=m) a %= m;
        if(b>=m) b %= m;
#ifndef __x86_64__
        uint64_t c = (long double)(a) * b / m;
        int64_t r = a * b - c * m;
        return r < 0 ? r%(int64_t)m + m : r%(int64_t)m;
#else
        __extension__ unsigned __int128 c = a;
        c *= b;
        c %= m;
        return c;
#endif
    }
};

template<>
struct mod_multiplies<uint32_t> : multiplies<uint32_t>
{
    uint32_t m;
    mod_multiplies(uint32_t _m) : m(_m) {}
    uint32_t operator()(uint32_t a, uint32_t b) const
    {
        return ((uint64_t)a * b) % m;
    }
};