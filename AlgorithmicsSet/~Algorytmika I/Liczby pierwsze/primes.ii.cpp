#include <bits/stdc++.h>
#include <ext/numeric>

// -*- ktl/ktl_debug_mode.cpp -*-

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

// -$- ktl/ktl_debug_mode.cpp -$-

// -*- ktl/math/mod_multiplies.cpp -*-

#include <functional>
#include <cstdint>

using std::multiplies;
using std::uint64_t; using std::int64_t;
using std::uint32_t;

template<typename T>
struct mod_multiplies;

template<>
struct mod_multiplies<uint64_t> : multiplies<uint64_t>
{
    uint64_t m;
    mod_multiplies(uint64_t _m) : m(_m) { KTL_DEBUG_ASSERT(m > 0); }
    uint64_t operator() (uint64_t a, uint64_t b) const
    {
        if(a >= m) a %= m;
        if(b >= m) b %= m;
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
    mod_multiplies(uint32_t _m) : m(_m) { KTL_DEBUG_ASSERT(m > 0); }
    uint32_t operator() (uint32_t a, uint32_t b) const
    {
        return ((uint64_t)a * b) % m;
    }
};

template<typename T>
T mod_mul(T a, T b, T m)
{
    mod_multiplies<T> M(m);
    return M(a, b);
}

// -$- ktl/math/mod_multiplies.cpp -$-


using namespace std;
using __gnu_cxx::power;

bool miller_rabin_primality_witness(uint64_t n, uint64_t d, size_t r, uint64_t a)
{
    mod_multiplies<uint64_t> Z(n);

    auto x = power(a, d, Z);

    if(x == 1 or x == n - 1)
        return true;

    for(size_t i = 1; i < r; i++)
    {
        x = Z(x, x);
        if(x == n - 1)
            return true;
    }

    return false;
}

const size_t TRIES = 32;

bool is_prime(uint64_t n)
{
    if(n <= 1) return false;
    else if(n <= 3) return true;
    else if(n % 2 == 0) return false;

    size_t r = __builtin_ctz(n - 1);
    uint64_t d = (n - 1) >> r;

    mt19937_64 gen((size_t)make_unique<char>().get());
    uniform_int_distribution<uint64_t> dis(2, n - 2);
    for(size_t t = 0; t < TRIES; t++)
    {
        auto a = dis(gen);
        if(not miller_rabin_primality_witness(n, d, r, a))
            return false;
    }

    return true;
}

int main()
{
    size_t n;
    cin >> n;
    while(n --> 0)
    {
        uint64_t a;
        cin >> a;
        cout << (is_prime(a) ? "TAK" : "NIE") << '\n';
    }
}
