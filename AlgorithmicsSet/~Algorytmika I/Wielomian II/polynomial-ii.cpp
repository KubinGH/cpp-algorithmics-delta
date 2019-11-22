#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t mod;
    mod_multiplies(uint64_t _mod) : mod(_mod) {}
    uint64_t operator() (uint64_t a, uint64_t b) { return (a*b) % mod; }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; uint64_t p;
    cin >> n >> p;

    vector<uint64_t> factorial(n+0xD);
    factorial[0] = 1;
    for(size_t k = 1; k < n+0xD; k++)
        factorial[k] = (factorial[k-1] * k) % p;

    mod_multiplies Zp(p);
    auto weak_binom = [&](uint64_t k, uint64_t i) {
        return k >= i ? (factorial[k] * power(factorial[i]*factorial[k-i] % p, p - 2, Zp)) % p : 0;
    };
    auto binom = [&](uint64_t k, uint64_t i) {
        uint64_t r = 1;
        while(k)
        {
            r *= weak_binom(k%p, i%p); r %= p;
            k /= p; i /= p;
        }
        return r;
    };

    vector<uint64_t> values(n+1);
    for(auto& y : values)
        cin >> y;

    uint64_t r = 0;
    for(size_t i = 0; i <= n; i++)
        r += ((i % 2 ? p-1 : 1) * binom(n + 1, i + 1))%p * values[n-i], r %= p;

    cout << r;
}
