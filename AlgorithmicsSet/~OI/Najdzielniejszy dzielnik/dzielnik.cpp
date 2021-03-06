#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;

template<typename T>
inline T gcd(T a, T b) { return __gcd(a, b); }

template<typename T>
struct mod_multiplies : multiplies<T>
{
    T m; mod_multiplies(T m) : m(m) {}
    T operator()(T a, T b) const
    {
        if(a < (1u << 31) and b < (1u << 31))
            return (a * b) % m;
        T r = 0;
        while(a)
        {
            if(a % 2)
                r += b, r %= m;
            a /= 2;
            b *= 2; b %= m;
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
bool miller_rabin_isprime(uint64_t n)
{
    if(n <= 1) return false; if(n <= 3) return true;
    if(n % 2 == 0) return false;
    mod_multiplies<uint64_t> M(n);
    uint64_t d = n - 1;
    uint32_t r = 0;
    while(d % 2 == 0) d /= 2, r++;
    for(uint64_t a : MR_PRIMES[1])
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

template<bool PRIME_CHECK = true>
uint64_t rho_pollard_get_factor(uint64_t n)
{
    if(n % 2 == 0)
        return 2;
    if(PRIME_CHECK and miller_rabin_isprime(n))
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

int main()
{
    srand(time(0));
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    unordered_map<uint64_t, uint32_t> M;
    vector<uint64_t> P;
    static bitset<1 << 23> S; S.set(); S[0] = S[1] = false;
    for(uint64_t i = 2; i < (1 << 21); i++)
    {
        if(not S[i])
            continue;
        P.push_back(i);
        for(uint64_t j = i*i; j < (1 << 21); j += i)
            S[j] = false;
    }
    for(uint32_t i = 0; i < n; i++)
    {
        uint64_t a;
        cin >> a;
        for(uint64_t p : P)
            while(a % p == 0)
                M[p]++, a /= p;
        if(a == 1)
            {}
        else if(miller_rabin_isprime(a))
            M[a]++;
        else
        {
            uint64_t d = rho_pollard_get_factor(a);
            M[d]++; M[a/d]++;
        }
    }
    uint32_t k = 0, d = 0;
    for(auto p : M)
    {
        if(p.second > k)
            k = p.second, d = 0;
        if(p.second == k)
            d++;
    }
    cout << k << "\n" << ((1llu << d) - 1);
}
