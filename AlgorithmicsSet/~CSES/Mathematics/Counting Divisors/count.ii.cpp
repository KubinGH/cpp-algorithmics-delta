#include <bits/stdc++.h>

// -*- ktl/ktl_debug_mode.cpp -*-

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

// -$- ktl/ktl_debug_mode.cpp -$-

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
        int64_t c = (long double)(a) * b / m;
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

// -*- ktl/math/factorization.cpp -*-

#include <functional>
#include <algorithm>
#include <cstddef>
#include <vector>
#include <ext/numeric>

using std::multiplies;
using std::function;
using std::vector;
using std::__lg; using std::__gcd; using __gnu_cxx::power;
using std::size_t;

constexpr size_t BRUTE_FACTOR_LIMIT = 1 << 13;

const auto __prime_cache_fact = linear_sieve(BRUTE_FACTOR_LIMIT);

template<typename T>
T pollard_rho_get_factor(T n)
{
    if(is_prime(n))
        return n;

    for(T c = 3; true; c++)
    {
        auto f = [c, n](T x) {
            return (mod_mul(x, x, n) + c) % n;
        };
        T x = 2, y = 2, d = 1;
        while(d == 1)
        {
            x = f(x);
            y = f(f(y));
            d = __gcd(x>y ? x-y : y-x, n);
        }
        if(d != n)
            return d;
    }
    return 1;
}

template<typename T>
T brent_get_factor(T n, T x0 = 2, T c = 1, bool composite_sure = false)
{
    if(not composite_sure and is_prime(n))
        return n;
    auto f = [c, n](T x) {
        return (mod_mul(x, x, n) + c) % n;
    };
    auto diff = [](T x, T y) {
        return x>y ? x - y : y - x;
    };

    T x = x0, g = 1, q = 1, xs, y;

    size_t m = 128, l = 1;
    while(g == 1)
    {
        y = x;
        for(size_t i = 1; i < l; i++)
            x = f(x);
        size_t k = 0;
        while(k < l and g == 1)
        {
            xs = x;
            for(size_t i = 0; i < m and i < l - k; i++)
            {
                x = f(x);
                q = mod_mul(q, diff(x, y), n);
            }
            g = __gcd(q, n);
            k += m;
        }
        l *= 2;
    }

    if(g == n)
    {
        do {
            xs = f(xs);
            g = __gcd(diff(xs, y), n);
        } while(g == 1);
        if(g == n)
            return brent_get_factor(n, x0, c + 3, true);
    }
    return g;
}

template<typename T, typename OutIterator, typename GetFactor>
OutIterator base_factorize(T n, OutIterator out, GetFactor F)
{
    if(n == 1)
        return out;
    T d = F(n);
    if(n == d)
        return *out++ = d;
    out = base_factorize(d, out, F);
    out = base_factorize(n/d, out, F);
    return out;
}

template<typename T>
struct default_get_factor
{
    T operator() (const T& x)
    {
#ifdef FORCE_POLLARD_RHO
        return pollard_rho_get_factor(x);
#else
        return brent_get_factor(x);
#endif
    }
};

template<typename T>
vector<T> factorize_int(T n)
{
    bool small = (2*n < power(BRUTE_FACTOR_LIMIT, 2));
    vector<T> result;
    for(auto p : __prime_cache_fact)
    {
        if(p > n or (small and p * p > n))
            break;
        while(n % p == 0)
            n /= p, result.push_back(p);
    }
    if(small)
    {
        if(n != 1)
            result.push_back(n);
        return result;
    }
    base_factorize(n, back_inserter(result), default_get_factor<T>{});
    sort(result.begin(), result.end());
    return result;
}

template<typename T>
vector<pair<T, size_t>> _pair_compress(const vector<T>& v)
{
    if(v.empty())
        return {};
    vector<pair<T, size_t>> out;
    out.emplace_back(v[0], 0);
    for(auto x : v)
    {
        if(out.back().first != x)
            out.emplace_back(x, 0);
        out.back().second++;
    }
    return out;
}

template<typename T>
vector<T> divisors(const vector<T>& P)
{
    const auto F = _pair_compress(P);
    vector<T> D;
    function<void(size_t, size_t, T)> gen = [&](size_t i, size_t k, T d) {
        if(i == F.size())
            D.push_back(d);
        else
        {
            if(k < F[i].second)
                gen(i, k + 1, d * F[i].first);
            gen(i + 1, 0, d);
        }
    };
    gen(0, 0, 1);
    sort(D.begin(), D.end());
    return D;
}

template<typename T>
vector<T> divisors(T n)
{
    return divisors(factorize_int(n));
}

// -$- ktl/math/factorization.cpp -$-


using namespace std;

int main()
{
    size_t q;
    cin >> q;

    while(q --> 0)
    {
        uint n;
        cin >> n;
        uint r = 1;
        for(auto& [p, e] : _pair_compress(factorize_int(n)))
            r *= e + 1;
        cout << r << '\n';
    }
}
