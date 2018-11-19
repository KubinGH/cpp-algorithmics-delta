#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    using weighted = pair<uint32_t, int64_t>;
    vector<vector<weighted>> graph(n);
    vector<vector<uint32_t>> of_index(n), from(n);
    vector<pair<uint32_t, uint32_t>> edge_index(m);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; int64_t w;
        cin >> u >> v >> w; u--; v--;
        graph[u].emplace_back(v, w);
        of_index[u].push_back(i);
        edge_index[i] = {u, graph[u].size()-1};
    }
    auto dijkstra = [&](const vector<vector<weighted>>& G) {
        vector<int64_t> D(n, INT64_MAX);
        vector<pair<uint32_t, uint32_t>> L(n, {-1u, -1u});
        priority_queue<weighted, vector<weighted>, greater<weighted>> Q;
        Q.emplace(0, 0); D[0] = 0;
        while(not Q.empty())
        {
            auto c = Q.top(); Q.pop();
            if(D[c.first] > c.second) continue;
            uint32_t u = c.first;
            for(uint32_t i = 0; i < G[u].size(); i++)
            {
                uint32_t v = G[u][i].first; int64_t w = G[u][i].second;
                if(D[u] + w < D[v])
                    Q.emplace(v, D[v] = D[u] + w), L[v] = {u, i};
            }
        }
        return make_pair(D, L);
    };
    vector<int64_t> D1, D2; vector<pair<uint32_t, uint32_t>> L1, L2;
    tie(D1, L1) = dijkstra(graph);
    if(D1[n-1] == INT64_MAX) { cout << -1; return 0; }
    vector<bool> to_invert(m);
    uint32_t v = n-1;
    while(v != 0)
    {
        uint32_t u = L1[v].first;
        to_invert[of_index[u][L1[v].second]] = true;
        v = u;
    }
    vector<vector<weighted>> new_graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u = edge_index[i].first;
        auto e = graph[u][edge_index[i].second];
        if(to_invert[i])
            new_graph[e.first].emplace_back(u, -e.second);
        else
            new_graph[u].push_back(e);
    }
    tie(D2, L2) = dijkstra(new_graph);
    if(D2[n-1] == INT64_MAX) { cout << -1; return 0; }

    cout << D1[n-1] + D2[n-1];
}
