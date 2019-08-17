#include <bits/stdc++.h>

using namespace std;

struct edge
{
    size_t v;
    int w;
};
struct edged
{
    size_t u, v;
    int w;
};

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

vector<int> sssp(const vector<vector<edge>>& graph, size_t source)
{
    const size_t n = graph.size();
    vector<int> dist(n, INT_MAX / 3);
    min_priority_queue<pair<int, int>> Q;
    auto maybe = [&](size_t v, int d) {
        if(d < dist[v]) Q.emplace(dist[v] = d, v);
    };
    maybe(source, 0);
    while(not Q.empty())
    {
        size_t u = Q.top().second; Q.pop();
        for(auto e : graph[u])
            maybe(e.v, dist[u] + e.w);
    }
    return dist;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, s, t;
    cin >> n >> m >> s >> t; s--; t--;

    vector<vector<edge>> graph(n), rgraph(n);
    vector<edged> edges;

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int w;
        cin >> u >> v >> w; u--; v--;
        graph[u].push_back({v, w});
        rgraph[v].push_back({u, w});
        edges.push_back({u, v, w});
    }

    auto dist_to = sssp(graph, s), dist_from = sssp(rgraph, t);

    for(auto e : edges)
        if(dist_to[e.u] + e.w + dist_from[e.v] == dist_to[t] + 1)
    {
        cout << "YES";
        return 0;
    }

    cout << "NO";
}
