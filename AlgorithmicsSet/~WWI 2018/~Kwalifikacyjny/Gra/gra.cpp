#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 17;
const uint64_t MOD = 1e9 + 7;

template<uint64_t M = MOD>
uint64_t mpow(uint64_t a, uint64_t b)
{
    a %= M; b %= M;
    uint64_t r = 1;
    while(b)
    {
        if(b % 2 == 1)
            r *= a, r %= M;
        b /= 2;
        a *= a; a %= M;
    }
    return r;
}
template<uint64_t M = MOD>
uint64_t invmod(uint64_t x) { return mpow(x % M, M - 2); }

int main()
{
    uint32_t b, p, k, s;
    cin >> b >> p >> k >> s;
    static uint64_t F[MAX];
    F[0] = 1;
    for(uint64_t i = 1; i < MAX; i++)
        F[i] = (F[i-1] * i) % MOD;
    uint64_t y = (F[p] * invmod(F[b] * F[p-b])) % MOD, x = (MOD + mpow(2, p) - y) % MOD;
    static uint64_t R[2][MAX];
    uint64_t r = 0;
    R[0][0] = 1;
    for(uint32_t i = 1; i <= k and i*(i+1)/2 <= s; i++)
    {
        uint32_t ic = i%2, ip = (i+1)%2;
        fill(begin(R[ic]), begin(R[ic]) + s+1, 0);
        uint64_t v = x + (i==k? y : 0llu);
        for(uint32_t j = i*(i+1)/2; j <= s; j++)
        {
            R[ic][j] = (y * R[ip][j-i]);
            if(j >= i)
                R[ic][j] += (v * R[ic][j-i]);
            R[ic][j] %= MOD;
        }
        r += R[ic][s];
        r %= MOD;
    }
    cout << r;
}
