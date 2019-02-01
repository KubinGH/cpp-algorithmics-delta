#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t m;
    mod_multiplies(uint64_t _m) : m(_m) {}
    uint64_t operator() (uint64_t a, uint64_t b) { return (a * b) % m; }
};

uint64_t factorial(uint64_t n, uint64_t mod)
{
    uint64_t r = 1;
    for(uint64_t i = 2; i <= n; i++)
        r = (r * i) % mod;
    return r;
}
uint64_t mod_inverse(uint64_t n, uint64_t mod)
{
    return power(n % mod, mod - 2, mod_multiplies(mod));
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, p;
    cin >> n >> m >> p;
    uint64_t a = factorial(n + m, p), b = factorial(n, p) * factorial(m, p);
    cout << (a * mod_inverse(b, p)) % p;
}
