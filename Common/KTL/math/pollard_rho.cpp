// Pollard's rho algorithm for finding factors.
// Complexity: O(n ^ 0.25 log n)
// Note: use the factorize_int function for actual factorization.
// Since it checks primes up to L = BRUTE_FACTOR_LIMIT before running
// Pollard's rho, at most log_L(n) runs will be executed.
// This should make the routine significantly faster.

// Last revision: March 2019

#pragma once

#include <algorithm>
#include <vector>

#include "linear_sieve.cpp"
#include "mod_multiplies.cpp"
#include "miller_rabin.cpp"

using std::multiplies;
using std::vector;
using std::__lg; using std::__gcd;

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