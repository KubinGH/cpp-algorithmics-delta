#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

template<typename T>
struct mod_multiplies : multiplies<T>
{
    T m; mod_multiplies(T _m) : m(_m) {}
    T operator()(T a, T b) const { return (a*b) % m; }
};
template<>
struct mod_multiplies<uint64_t> : multiplies<uint64_t>
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
        uint64_t x = power(a, d, M);
        if(x == 1 or x == n - 1)
            continue;
        for(uint32_t i = 0; i < r - 1; i++)
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
bool miller_rabin_isprime(uint64_t n)
{
    return miller_rabin_isprime(n, {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37});
}


int main()
{
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint64_t n;
        cin >> n;
        cout << (miller_rabin_isprime(n) ? "YES\n" : "NO\n");
    }
}

