#include <bits/stdc++.h>

using namespace std;

const size_t PRE = 1 << 23;
const int64_t MOD = 1e9 + 7, inv2 = 500000004;
int8_t mu[PRE]; int16_t Mp[PRE];

unordered_map<uint64_t, int32_t> cache;

int64_t M(uint64_t n)
{
    if(n < PRE)
        return Mp[n];
    if(cache.count(n))
        return cache[n];

    int64_t r = 0;
    for(uint64_t i = 2, i1; i <= n; i = i1 + 1)
        i1 = n / (n / i), r += M(n / i) * int64_t(i1 - i + 1);

    return cache[n] = 1 - r;
}

int64_t F(uint64_t n)
{
    int64_t r = 0;
    for(uint64_t i = 1, i1; i <= n; i = i1 + 1)
    {
        i1 = n / (n / i);
        auto f = (n / i) % MOD;
        auto x = (M(i1) - M(i-1)) * int64_t(f*f % MOD);
        x = (x%MOD + MOD) % MOD;
        r += x; r %= MOD;
    }
    return (1 + r) * inv2 % MOD;
}

int main()
{
    mu[1] = 1;
    for(size_t d = 1; d < PRE; d++)
        for(size_t k = 2*d; k < PRE; k += d)
            mu[k] -= mu[d];

    for(size_t k = 1; k < PRE; k++)
        Mp[k] = Mp[k-1] + mu[k];
    cache.reserve(1 << 24);

    uint64_t n;
    cin >> n;

    cout << F(n);
}
