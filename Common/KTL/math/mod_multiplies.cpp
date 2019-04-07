// Modular multiplication of 64-bit integers using the approximation method
// in constant time.
// Will probably fail for numbers larger than ~2^63, but this is enough
// most of the time.

// Last revision: Beginning of 2019

#pragma once

#include <functional>
#include <cstdint>

using std::multiplies; using std::uint64_t; using std::int64_t;

struct mod_multiplies : multiplies<uint64_t>
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

