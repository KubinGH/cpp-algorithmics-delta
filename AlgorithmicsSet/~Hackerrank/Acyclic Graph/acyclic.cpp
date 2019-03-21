#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 1 << 16;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;

    vector<vector<uint32_t>> graph(n);
    vector<uint32_t> indegree(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t v, u;
        cin >> v >> u; v--; u--;
        graph[u].push_back(v);
        indegree[v]++;
    }

    vector<uint32_t> topo; topo.reserve(n);
    for(uint32_t u = 0; u < n; u++)
        if(not indegree[u])
            topo.push_back(u);

    for(uint32_t t = 0; t < topo.size(); t++)
    {
        uint32_t u = topo[t];
        for(uint32_t v : graph[u])
            if(not --indegree[v])
                topo.push_back(v);
    }

    vector<bitset<MAX_N>> sources(n);
    for(uint32_t u : topo)
    {
        sources[u].set(u);
        for(uint32_t v : graph[u])
            sources[v] |= sources[u];
    }

    uint32_t result = 0;
    for(uint32_t u = 0; u < n; u++)
        if(2 * sources[u].count() >= n)
            result++;
    cout << result;
}
