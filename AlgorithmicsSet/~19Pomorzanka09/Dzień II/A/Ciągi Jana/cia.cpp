#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint64_t MOD = 1e9 + 7;

struct mod_multiplies : multiplies<uint>
{
    uint operator() (uint a, uint b) { return (uint64_t)a*b % MOD; }
} Zm;

int main()
{
    uint n, k;
    cin >> n >> k;

    map<uint, vector<uint>> div_cache;
    auto divisors = [&](uint x) {
        if(div_cache.count(x)) return div_cache[x];
        for(size_t d = 1; d*d <= x; d++)
        {
            if(x % d == 0)
            {
                div_cache[x].push_back(d);
                if(d*d != x) div_cache[x].push_back(x / d);
            }
        }
        return div_cache[x];
    };

    map<uint, uint> f_cache;
    function<uint(uint)> f = [&](uint d) {
        if(f_cache.count(d)) return f_cache[d];
        uint s = 0;
        for(uint x : divisors(d))
            if(x < d)
                s += f(x), s %= MOD;
        return f_cache[d] = (MOD + power(k, (d+1)/2, Zm) - s) % MOD;
    };

    uint64_t resulto = 0;
    for(uint d : divisors(n))
        resulto += (uint64_t)f(d) * (d/(2 - d%2)), resulto %= MOD;

    cout << resulto;
}
