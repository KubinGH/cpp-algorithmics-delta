#include <bits/stdc++.h>

using namespace std;

const uint64_t oo = UINT64_MAX / 3;
using graph_t = vector<vector<pair<size_t, uint>>>;
template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

vector<uint64_t> sssp(size_t source, const graph_t& graph)
{
    vector<uint64_t> dist(graph.size(), +oo);
    vector<bool> lock(graph.size());
    min_priority_queue<pair<uint64_t, size_t>> Q;

    auto maybe = [&](size_t v, uint64_t d) {
        if(d < dist[v])
            Q.emplace(dist[v] = d, v);
    };
    maybe(source, 0);
    while(not Q.empty())
    {
        auto [_, u] = Q.top(); Q.pop();
        if(lock[u]) continue;
        lock[u] = true;
        for(auto [v, w] : graph[u])
            maybe(v, dist[u] + w);
    }

    return dist;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph_t graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; uint w;
        cin >> u >> v >> w; u--; v--;
        graph[v].emplace_back(u, w);
    }

    auto dist = sssp(0, graph);
    for(size_t i = 0; i < n; i++)
        if(dist[i] != +oo)
            cout << dist[i] << '\n';
        else
            cout << "+oo\n";
}
