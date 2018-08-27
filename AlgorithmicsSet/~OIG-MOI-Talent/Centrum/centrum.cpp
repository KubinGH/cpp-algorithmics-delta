#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 4096;

static vector<uint32_t> graph[MAX];

uint32_t dfs_distlim(uint32_t u, uint32_t imp, uint32_t d, uint32_t lim)
{
    uint32_t r = 1;
    for(uint32_t v : graph[u])
        if(v != imp and d+1 <= lim)
            r += dfs_distlim(v, u, d + 1, lim);
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    // global vector<uint32_t> graph[MAX];
    vector<pair<uint32_t, uint32_t>> edges; edges.reserve(n - 1);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.emplace_back(u, v);
    }
    uint32_t result = 0;
    if(k % 2)
    {
        for(auto e : edges)
        {
            uint32_t u, v; tie(u, v) = e;
            uint32_t r = dfs_distlim(u, v, 0, k/2)
                       + dfs_distlim(v, u, 0, k/2);
            result = max(result, r);
        }
    }
    else
    {
        for(uint32_t u = 0; u < n; u++)
        {
            uint32_t r = 1;
            for(uint32_t v : graph[u])
                r += dfs_distlim(v, u, 1, k/2);
            result = max(result, r);
        }
    }
    cout << result;
}
