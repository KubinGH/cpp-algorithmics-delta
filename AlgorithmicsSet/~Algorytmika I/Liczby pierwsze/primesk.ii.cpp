#include <bits/stdc++.h>

// -*- ktl/util/gcc_bit_ext.cpp -*-

#define ADAPT_BIT_EXT_TO_TEMPLATE(__new_name, __name_int, __name_long, __name_llong) \
    unsigned __new_name(int x) { return __name_int(x); }                    \
    unsigned __new_name(unsigned int x) { return __name_int(x); }           \
    unsigned __new_name(long x) { return __name_long(x); }                  \
    unsigned __new_name(unsigned long x) { return __name_long(x); }         \
    unsigned __new_name(long long x) { return __name_llong(x); }            \
    unsigned __new_name(unsigned long long x) { return __name_llong(x); }

ADAPT_BIT_EXT_TO_TEMPLATE(popcount, __builtin_popcount, __builtin_popcountl, __builtin_popcountll)
ADAPT_BIT_EXT_TO_TEMPLATE(clz, __builtin_clz, __builtin_clzl, __builtin_clzll)
ADAPT_BIT_EXT_TO_TEMPLATE(ctz, __builtin_ctz, __builtin_ctzl, __builtin_ctzll)

#undef ADAPT_BIT_EXT_TO_TEMPLATE

// -$- ktl/util/gcc_bit_ext.cpp -$-

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

// -*- ktl/math/linear_sieve.cpp -*-

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

using std::size_t;
using std::__lg;
using std::pair; using std::vector;

pair<vector<size_t>, vector<size_t>> linear_sieve_dual(size_t n)
{
    KTL_DEBUG_ASSERT(n > 0);
    vector<size_t> P, M(n);
    P.reserve(2 * n / __lg(n));
    for(size_t x = 2; x < n; x++)
    {
        if(not M[x])
            M[x] = x, P.push_back(x);
        for(size_t i = 0; i < P.size() and x * P[i] < n and P[i] <= M[x]; i++)
            M[x * P[i]] = P[i];
    }
    return {P, M};
}

vector<size_t> linear_sieve(size_t n)
{
    return linear_sieve_dual(n).first;
}

// -$- ktl/math/linear_sieve.cpp -$-

// -*- ktl/math/primality.cpp -*-

#include <ext/numeric>
#include <cstddef>
#include <vector>

using std::size_t; using std::uintmax_t;
using std::vector;
using __gnu_cxx::power;

constexpr size_t SMALL_PRIMES_LIMIT = 1 << 10;
const auto __prime_cache_small = linear_sieve(SMALL_PRIMES_LIMIT);

template<typename T>
bool miller_rabin_primality_witness(T n, T d, size_t r, T a)
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
        if(not miller_rabin_primality_witness(n, d, r, a))
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

// -$- ktl/math/primality.cpp -$-


using namespace std;

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
