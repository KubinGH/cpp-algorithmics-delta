#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;
const uint32_t LIM = 1e9 + 9;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, start, goal;
    cin >> n >> m >> start >> goal; start--; goal--;
    static array<vector<uint32_t>, MAX> graph;
    static array<uint32_t, MAX> incoming;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        incoming[v]++;
    }
    static array<uint32_t, MAX> topological; uint32_t ti = 0;
    for(uint32_t i = 0; i < n; i++)
        if(incoming[i] == 0)
            topological[ti++] = i;
    static array<uint32_t, MAX> ways;
    ways[start] = 1;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t u = topological[i];
        for(uint32_t v : graph[u])
        {
            incoming[v]--;
            ways[v] += ways[u];
            ways[v] %= LIM;
            if(incoming[v] == 0)
            {
                topological[ti++] = v;
            }
        }
    }
    cout << ways[goal];
}
