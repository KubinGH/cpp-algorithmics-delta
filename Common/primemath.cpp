#include <algorithm>
#include <iostream>
#include <ext/numeric>
#include <cassert>
#include <list>

using namespace std;

template<typename T>
inline T gcd(T a, T b) { return __gcd(a, b); }

template<typename T>
struct mod_multiplies : multiplies<T>
{
    T m; mod_multiplies(T m) : m(m) {}
    T operator()(T a, T b) const
    {
        T r = 0;
        while(a)
        {
            if(a % 2)
                r += b, r %= m;
            a /= 2;
            b *= 2, b %= m;
        }
        return r;
    }
};
using __gnu_cxx::power;
template<typename T>
T modpower(T a, T b, T m) { return power(a, b, mod_multiplies<T>(m)); }


// 0: 2^32 - {2, 7, 61} (3)
// 1: 3.8 * 10^18 - {2, 3, 5, 7, 11, 13, 17, 19, 23} (9)
// 2: 2^64 - {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37} (12)
const vector<uint64_t> MR_PRIMES[3] = {
    {2, 7, 61},
    {2, 3, 5, 7, 11, 13, 17, 19, 23},
    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
};
bool miller_rabin_isprime(uint64_t n, const vector<uint64_t>& W)
{
    if(n <= 1) return false; if(n <= 3) return true;
    if(n % 2 == 0) return false;
    mod_multiplies<uint64_t> M(n);
    uint64_t d = n - 1;
    uint32_t r = 0;
    while(d % 2 == 0) d /= 2, r++;
    for(uint64_t a : W)
    {
        if(a + 2 > n)
            continue;
        uint64_t x = modpower(a, d, n);
        if(x == 1 or x == n - 1)
            continue;
        bool comp = true;
        for(uint32_t i = 0; i < r - 1; i++)
        {
            x = M(x, x);
            if(x == 1)
                return false;
            if(x == n - 1)
            {
                comp = false;
                break;
            }
        }
        if(comp)
            return false;
    }
    return true;
}
bool miller_rabin_isprime(uint64_t n)
{
    if(n < (1llu << 32))
        return miller_rabin_isprime(n, MR_PRIMES[0]);
    else if(n < ((1llu<<61)+(1llu<<60)+(1llu<<59)-(1llu<<58)))
        return miller_rabin_isprime(n, MR_PRIMES[1]);
    else
        return miller_rabin_isprime(n, MR_PRIMES[2]);
}

template<typename T>
bool sqrt_isprime(T n)
{
    if(n <= 1) return false; if(n <= 3) return true;
    for(T i = 2; i * i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}


uint64_t rho_pollard_get_factor(uint64_t n)
{
    if(n % 2 == 0)
        return 2;
    if(miller_rabin_isprime(n))
        return n;
    mod_multiplies<uint64_t> M(n);
    for(uint64_t c = 1; true; c++)
    {
        uint64_t x = 2, y = 2, d = 1;
        while(d == 1)
        {
            x = (M(x, x) + c) % n;
            y = (M(y, y) + c) % n; y = (M(y, y) + c) % n;
            d = gcd(x>y ? x-y : y-x, n);
        }
        if(d != n)
            return d;
    }
    return 1;
}

list<uint64_t> rho_pollard_factorize(uint64_t n)
{
    if(n == 1)
        return {};
    uint64_t d = rho_pollard_get_factor(n);
    list<uint64_t> result;
    if(miller_rabin_isprime(d))
        result.merge({d});
    else
        result.merge(rho_pollard_factorize(d));
    if(miller_rabin_isprime(n/d))
        result.merge({n/d});
    else
        result.merge(rho_pollard_factorize(n/d));
    return result;
}

uint32_t pi_prime_count(uint64_t n)
{
    uint32_t r = 0;
    for(uint64_t i = 2; i <= n; i++)
        r += miller_rabin_isprime(i);
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cout.tie(0);
    for(uint32_t i = 1; i < (1 << 10); i++)
    {
        uint64_t j = i + (1llu << 50);
        bool a = miller_rabin_isprime(j, MR_PRIMES[2]),
             b = sqrt_isprime(j);
        assert(a == b);
        if(a) cout << j << ": " << a << "/" << b << endl;
        uint64_t k = 1;
        for(uint64_t x : rho_pollard_factorize(j))
        {
            assert(miller_rabin_isprime(x));
            k *= x;
        }
        assert(j == k);
    }
    /*
    for(uint64_t i = 1 << 26; i < (1 << 27); i++)
    {
        uint64_t j = 1;
        for(uint64_t x : rho_pollard_factorize(i))
        {
            assert(miller_rabin_isprime(x));
            j *= x;
        }
        assert(i == j);
        if(i % (1 << 20) == 0)
            cout << i << endl;
    }
    */
}
