#include <bits/stdc++.h>

using namespace std;

struct edge { uint32_t v; uint64_t w; };

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

vector<uint64_t> dijkstra(const vector<vector<edge>>& graph, uint32_t initial)
{
    min_priority_queue<pair<uint64_t, uint32_t>> Q;
    Q.emplace(0, initial);
    vector<uint64_t> D(graph.size(), -1llu); D[initial] = 0;
    while(not Q.empty())
    {
        auto c = Q.top(); Q.pop(); uint32_t u = c.second;
        if(D[u] < c.first) continue;
        for(auto e : graph[u])
            if(D[u] + e.w < D[e.v])
                Q.emplace(D[e.v] = D[u] + e.w, e.v);
    }
    return D;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<edge>> graph[2], graphT[2];
    for(uint32_t f = 0; f < 2; f++)
        graph[f].resize(n), graphT[f].resize(n);
    vector<vector<edge>> result_graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; uint64_t p, q;
        cin >> u >> v >> p >> q; u--; v--;
        graph[0][u].push_back({v, p}), graphT[0][v].push_back({u, p});
        graph[1][u].push_back({v, q}), graphT[1][v].push_back({u, q});
        result_graph[u].push_back({v, 0});
    }
    for(uint32_t f = 0; f < 2; f++)
    {
        vector<uint64_t> paths = dijkstra(graphT[f], n-1);
        vector<bool> vis(n);
        stack<uint32_t> S; S.push(0); vis[0] = true;
        while(not S.empty())
        {
            uint32_t u = S.top(); S.pop();
            for(uint32_t i = 0; i < graph[f][u].size(); i++)
            {
                auto e = graph[f][u][i];
                if(paths[e.v] + e.w > paths[u])
                    result_graph[u][i].w++;
                if(not vis[e.v])
                {
                    vis[e.v] = true;
                    S.push(e.v);
                }
            }
        }
    }
    cout << dijkstra(result_graph, 0)[n-1];
}
