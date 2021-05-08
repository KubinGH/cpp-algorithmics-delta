// Pollard's rho & Brent's algorithm for finding factors.
// Complexity: average O(n^0.25 log n)
// Note: use the factorize_int function for actual factorization.
// Since it checks primes up to L = BRUTE_FACTOR_LIMIT before running
// Brent (Pollard's rho if FORCE_POLLARD_RHO is defined),
// at most log_L(n) runs will be executed.
// This should make the routine significantly faster.
// Brent's method benchmark:
// 3 times faster on random up to 2^60, 2 times faster on random up to 2^50
//  (in comparison with Pollard's rho)
// Brent is based on https://cp-algorithms.com/algebra/factorization.html,
//  note: sometimes a new generator is needed and Brent calls itself recursively

// Last revision: June 2019

#pragma once

#include <functional>
#include <algorithm>
#include <cstddef>
#include <vector>
#include <ext/numeric>
#include "linear_sieve.cpp"
#include "mod_multiplies.cpp"
#include "primality.cpp"

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
