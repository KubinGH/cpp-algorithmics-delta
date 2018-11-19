#include <bits/stdc++.h>

using namespace std;

struct edge_t { uint32_t u, v, w; };
typedef tuple<uint32_t, uint32_t, uint32_t> tri_u32;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t s, n, m;
    cin >> s >> n >> m;
    vector<uint32_t> sources(s);
    vector<bool> source_used(n);
    for(uint32_t i = 0; i < s; i++)
    {
        cin >> sources[i]; sources[i]--;
        if(source_used[sources[i]])
        {
            cout << "0";
            return 0;
        }
        source_used[sources[i]] = true;
    }
    vector<vector<edge_t>> graph(n);
    vector<edge_t> edges; edges.reserve(m);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w; u--, v--;
        graph[u].push_back({u, v, w});
        graph[v].push_back({v, u, w});
        edges.push_back({u, v, w});
    }
    vector<uint32_t> dist(n, -1u), first_visitor(n, -1u);
    priority_queue<tri_u32, vector<tri_u32>, greater<tri_u32>> Q;
    for(uint32_t i = 0; i < s; i++)
    {
        uint32_t z = sources[i];
        dist[z] = 0;
        first_visitor[z] = i;
        Q.emplace(0, z, i);
    }
    while(not Q.empty())
    {
        uint32_t d, u, z;
        tie(d, u, z) = Q.top(); Q.pop();
        if(d > dist[u]) continue;
        first_visitor[u] = z;
        for(auto e : graph[u])
        {
            if(dist[u] + e.w < dist[e.v])
                Q.emplace(dist[e.v] = dist[u] + e.w, e.v, z);
        }
    }
    uint32_t result = (-1u)/3;
    for(auto e : edges)
    {
        if(first_visitor[e.u] != first_visitor[e.v])
            result = min(result, dist[e.u] + dist[e.v] + e.w);
    }
    cout << result * 3;
}
