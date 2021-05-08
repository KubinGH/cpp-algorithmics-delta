#include <bits/stdc++.h>

using namespace std;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

constexpr uint mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<size_t, int>>> graph(n+1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    vector<bool> lock(n+1);
    vector<int64_t> dist(n+1, INT64_MAX/3-0xD);
    min_heap<pair<int64_t, size_t>> que;
    auto maybe = [&](size_t u, int64_t d) {
        if(d < dist[u])
            que.emplace(dist[u] = d, u);
    };
    maybe(1, 0);

    vector<size_t> order;
    while(not que.empty())
    {
        auto u = que.top().second; que.pop();
        if(lock[u])
            continue;
        lock[u] = true;
        for(auto [v, w] : graph[u])
            maybe(v, dist[u] + w);
        order.push_back(u);
    }

    vector<uint> ways(n+1);
    vector<int> min_edges(n+1, INT_MAX/3-0xD), max_edges(n+1, INT_MIN/3+0xD);

    ways[1] = 1;
    min_edges[1] = max_edges[1] = 0;
    for(auto u : order)
    {
        for(auto [v, w] : graph[u])
          if(dist[v] == dist[u] + w)
        {
            ways[v] += ways[u]; ways[v] %= mod;
            min_edges[v] = min(min_edges[v], min_edges[u] + 1);
            max_edges[v] = max(max_edges[v], max_edges[u] + 1);
        }
    }

    cout << dist[n] << ' ' << ways[n] << ' ' << min_edges[n] << ' ' << max_edges[n] << endl;
}
