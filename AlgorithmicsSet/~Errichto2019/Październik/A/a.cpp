#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

struct edge { size_t v; uint w; };

vector<uint64_t> dijkstra(const vector<vector<edge>>& graph, size_t source)
{
    vector<uint64_t> dist(graph.size(), UINT64_MAX);
    vector<bool> vis(graph.size());
    min_priority_queue<pair<uint64_t, size_t>> Q;
    auto maybe = [&](size_t v, uint64_t d) {
        if(not vis[v] and d < dist[v])
            Q.emplace(dist[v] = d, v);
    };
    maybe(source, 0);
    while(not Q.empty())
    {
        auto u = Q.top().second; Q.pop();
        if(vis[u]) continue;
        for(auto e : graph[u])
            maybe(e.v, dist[u] + e.w);
    }
    return dist;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<edge>> graph(n);
    vector<tuple<size_t, size_t, uint>> edges(2*m);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; uint w;
        cin >> u >> v >> w; u--; v--;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
        edges[2*i  ] = {u, v, w};
        edges[2*i+1] = {v, u, w};
    }

    auto dist = dijkstra(graph, 0);

    vector<size_t> prev(n, SIZE_MAX);

    for(auto e : edges)
    {
        size_t u, v; uint w;
        tie(u, v, w) = e;
        if(dist[u] + w == dist[v])
            prev[v] = u;
    }

    if(dist[n-1] != UINT64_MAX)
    {
        size_t u = n - 1;
        vector<size_t> path = {n - 1};
        while(u != 0)
            path.push_back(u = prev[u]);
        reverse(path.begin(), path.end());
        for(auto v : path)
            cout << v+1 << " ";
    }
    else
        cout << "-1";
}
