#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<pair<size_t, int>>>;

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const int64_t oo = INT64_MAX / 3;

vector<int64_t> sssp(const graph_t& graph, size_t source)
{
    const size_t n = graph.size();

    vector<int64_t> dist(n, +oo);
    vector<bool> lock(n);

    min_priority_queue<pair<int64_t, size_t>> Q;
    auto maybe = [&](size_t u, int64_t d) {
        if(d < dist[u])
            Q.emplace(dist[u] = d, u);
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

    vector<tuple<size_t, size_t, int>> E;
    graph_t G(n), H(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int w;
        cin >> u >> v >> w; u--; v--;
        E.emplace_back(u, v, w);
        G[u].emplace_back(v, w);
        H[v].emplace_back(u, w);
    }

    auto D = sssp(G, 0), B = sssp(H, n - 1);

    if(D[n - 1] == +oo)
    {
        cout << "-1\n";
        return 0;
    }

    vector<vector<size_t>> S(n);
    for(auto [u, v, w] : E)
        if(D[u] + B[v] + w == D[n - 1])
            S[u].push_back(v);

    bool e = false;
    for(size_t u = 0; u < n; u++)
        if(S[u].size() > 1)
            e = true;

    if(e)
    {
        cout << D[n - 1] << '\n';
        return 0;
    }

    int64_t opt = +oo;

    for(auto [u, v, w] : E)
    {
        auto d = D[u] + w + B[v];
        if(d != D[n - 1])
            opt = min(opt, d);
    }

    cout << (opt != +oo ? opt : -1) << '\n';
}
