#include <bits/stdc++.h>
#include <ext/numeric>

#ifdef _KTL_DEBUG
#include <cassert>
#define KTL_DEBUG_ASSERT(__EXPR) assert(__EXPR)
#else
#define KTL_DEBUG_ASSERT(_)
#endif

using __gnu_cxx::power;
using namespace std;

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


#define ADAPT_BIT_EXT_TO_TEMPLATE(__new_name, __name_int, __name_long, __name_llong)                        \
    template<typename T> unsigned __new_name(T x);                                                          \
    template<> unsigned __new_name<unsigned int>(unsigned int x) { return __name_int(x); }                  \
    template<> unsigned __new_name<unsigned long>(unsigned long x) { return __name_long(x); }               \
    template<> unsigned __new_name<unsigned long long>(unsigned long long x) { return __name_llong(x); }

ADAPT_BIT_EXT_TO_TEMPLATE(popcount, __builtin_popcount, __builtin_popcountl, __builtin_popcountll)
ADAPT_BIT_EXT_TO_TEMPLATE(clz, __builtin_clz, __builtin_clzl, __builtin_clzll)
ADAPT_BIT_EXT_TO_TEMPLATE(ctz, __builtin_ctz, __builtin_ctzl, __builtin_ctzll)

#undef ADAPT_BIT_EXT_TO_TEMPLATE

template<typename T>
bool miller_rabin_test(T n, const vector<uintmax_t>& W)
{
    if(n <= 1) return false;
    else if(n <= 3) return true;
    else if(n % 2 == 0) return false;
    mod_multiplies<T> M(n);
    size_t r = ctz(n - 1);
    T d = (n - 1) >> r;
    for(auto a1 : W)
    {
        T a = a1 % n;
        if(not a)
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
bool is_prime(T n);

template<>
bool is_prime<uint32_t>(uint32_t n)
{
    if(n < 341531)
        return miller_rabin_test(n, {9345883071009581737ull});
    else if(n < 1050535501)
        return miller_rabin_test(n, {336781006125ull, 9639812373923155ull});
    else
        return miller_rabin_test(n, {2, 7, 61});
}

template<>
bool is_prime<uint64_t>(uint64_t n)
{
    if(n < ((uint64_t)1 << 31))
        return is_prime((uint32_t)n);
    else if(n < 55245642489451ull)
        return miller_rabin_test(n, {2, 141889084524735ull, 1199124725622454117ull, 11096072698276303650ull});
    else
        return miller_rabin_test(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

constexpr size_t BRUTE_FACTOR_LIMIT = 1 << 10;

template<typename T>
T rho_pollard_get_factor(T n)
{
    if(n % 2 == 0)
        return 2;
    if(is_prime(n))
        return n;
    mod_multiplies<T> M(n);
    for(T c = 3; true; c++)
    {
        T x = 2, y = 2, d = 1;
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

template<typename T, typename OutIterator>
OutIterator rho_pollard_factorize(T n, OutIterator out)
{
    if(n == 1)
        return out;
    T d = rho_pollard_get_factor(n);
    if(n == d)
        return *out++ = d;
    out = rho_pollard_factorize(d, out);
    out = rho_pollard_factorize(n/d, out);
    return out;
}

const auto __prime_cache_fact = linear_sieve(BRUTE_FACTOR_LIMIT);

template<typename T>
vector<T> factorize_int(T n)
{
    vector<T> result;
    for(auto p : __prime_cache_fact)
        while(n % p == 0)
            n /= p, result.push_back(p);
    rho_pollard_factorize(n, back_inserter(result));
    sort(result.begin(), result.end());
    return result;
}

template<typename T>
vector<T> divisors(T n)
{
    const auto F = factorize_int(n);
    vector<T> D;
    for(size_t i = 0; i < (size_t(1) << F.size()); i++)
    {
        T d = 1;
        for(size_t k = 0; k < F.size(); k++)
            if(i & (size_t(1) << k))
                d *= F[k];
        D.push_back(d);
    }
    sort(D.begin(), D.end());
    D.erase(unique(D.begin(), D.end()), D.end());
    return D;
}

int main()
{
    uint64_t n;
    while(cin >> n)
    {
        if(n == 0) break;
        auto F = factorize_int(n);
        uint64_t p = F.front(), k = 0;
        for(auto f : F)
        {
            if(p != f)
                cout << p << "^" << k << " ", p = f, k = 0;
            k++;
        }
        cout << p << "^" << k << endl;
    }

}
