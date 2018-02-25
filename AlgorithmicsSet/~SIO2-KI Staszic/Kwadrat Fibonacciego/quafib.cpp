#include <bits/stdc++.h>

using namespace std;

const int64_t MOD = 1e9 + 7;

unordered_map<int64_t, int64_t> CACHE;
int64_t F(int64_t n)
{
    if(CACHE.find(n) != CACHE.end())
        return CACHE[n];
    uint64_t k = (n + (n % 2)) / 2, u, v;
    if(n == 0)
        return 0;
    else if(n == 1 or n == 2)
        return 1;
    u = F(k), v = F(k - 1);
    if(n % 2)
        CACHE[n] = (u*u + v*v) % MOD;
    else
        CACHE[n] = ((2*v + u) * u) % MOD;
    return CACHE[n];
}

int main()
{
    int64_t a, b;
    cin >> a >> b;
    cout << (((F(b+1)*F(b+2))%MOD) - ((F(a)*F(a+1))%MOD) + MOD) % MOD;
}
