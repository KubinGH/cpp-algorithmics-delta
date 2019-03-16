#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9 + 7;

vector<uint64_t> cache;
uint64_t solve(uint32_t u, bool free, const vector<vector<uint32_t>>& graph, uint32_t lock = -1u)
{
    if(cache[free*graph.size()+u] != -1llu)
        return cache[free*graph.size()+u];
    uint64_t result = 1;
    for(uint32_t v : graph[u]) if(v != lock)
        result *= solve(v, true, graph, u), result %= MOD;
    if(free)
    {
        vector<uint64_t> suf(graph[u].size() + 1);
        suf.back() = 1;
        for(uint32_t i = graph[u].size(), v; i --> 0; )
        {
            v = graph[u][i];
            suf[i] = suf[i+1];
            if(v != lock)
                suf[i] *= solve(v, true, graph, u), suf[i] %= MOD;
        }
        uint64_t pref = 1;
        for(uint32_t i = 0, v; i < graph[u].size(); i++) if((v = graph[u][i]) != lock)
        {
            uint64_t curr = (((suf[i+1] * pref) % MOD) * solve(v, false, graph, u)) % MOD;
            pref *= solve(v, true, graph, u); pref %= MOD;
            result += curr; result %= MOD;
        }
    }
    return cache[free*graph.size()+u] = result;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    cache.resize(2 * n, -1llu);
    cout << solve(0, true, graph);
}
