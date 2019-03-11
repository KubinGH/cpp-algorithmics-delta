#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t m;
    mod_multiplies(uint64_t _m) : m(_m) {}
    uint64_t operator() (uint64_t a, uint64_t b) const { return (a*b) % m; }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, s; bool r; uint64_t p;
    cin >> n >> s >> p >> r; s--;

    mod_multiplies Zp(p);

    auto mod_inverse = [&](uint64_t a) {
        return power(a, p - 2, Zp);
    };
    vector<uint64_t> F_cache;
    F_cache.push_back(1);
    auto factorial = [&](uint32_t n) {
        while(F_cache.size() <= n)
            F_cache.push_back(Zp(F_cache.back(), F_cache.size()));
        return F_cache[n];
    };
    auto binom = [&](uint32_t n, uint32_t k) {
        return Zp(factorial(n), mod_inverse(Zp(factorial(k), factorial(n-k))));
    };

    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<uint64_t> pop(n);
    for(uint32_t u = 0; u < n; u++)
        cin >> pop[u];

    vector<bool> vis(n);
    function<pair<uint64_t, uint64_t>(uint32_t)> solve = [&](uint32_t u) {
        vis[u] = true;
        uint64_t leaves = 0, result = 1;
        for(uint32_t v : graph[u]) if(not vis[v])
        {
            auto c = solve(v);
            leaves += c.first;
            result = Zp(result, c.second);
        }
        if(leaves > 0)
        {
            if(r)
                result = Zp(result, power(leaves, pop[u], Zp));
            else
                result = Zp(result, binom(pop[u]+leaves-1, leaves-1));
        }
        else
            leaves++;
        return make_pair(leaves, result);
    };

    cout << solve(s).second;

}
