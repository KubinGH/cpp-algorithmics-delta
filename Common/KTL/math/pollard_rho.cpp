// Pollard's rho algorithm for finding factors.
// Complexity: O(n^0.25 log n)
// Note: use the factorize_int function for actual factorization.
// Since it checks primes up to L = BRUTE_FACTOR_LIMIT before running
// Pollard's rho, at most log_L(n) runs will be executed.
// This should make the routine significantly faster.

// Last revision: March 2019

#pragma once

#include <functional>
#include <algorithm>
#include <cstddef>
#include <vector>
#include "linear_sieve.cpp"
#include "mod_multiplies.cpp"
#include "miller_rabin.cpp"

using std::multiplies;
using std::function;
using std::vector;
using std::__lg; using std::__gcd;
using std::size_t;

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
    {
        if(p > n)
            break;
        while(n % p == 0)
            n /= p, result.push_back(p);
    }
    rho_pollard_factorize(n, back_inserter(result));
    sort(result.begin(), result.end());
    return result;
}

template<typename T>
vector<pair<T, size_t>> _pair_compress(const vector<T>& v)
{
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
vector<T> divisors(T n)
{
    const auto F = _pair_compress(factorize_int(n));
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


#include <iostream>
using namespace std;
int main()
{
    unsigned long x = 36;
    for(auto d : divisors(x))
        cout << d << endl;
}
