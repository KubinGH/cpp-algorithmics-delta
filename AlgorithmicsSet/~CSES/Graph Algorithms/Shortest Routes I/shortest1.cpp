#include <bits/stdc++.h>

using namespace std;

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

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
    vector<int64_t> dist(n+1, INT64_MAX);
    min_heap<pair<int64_t, size_t>> que;
    auto maybe = [&](size_t u, int64_t d) {
        if(d < dist[u])
            que.emplace(dist[u] = d, u);
    };

    maybe(1, 0);
    while(not que.empty())
    {
        auto [_, u] = que.top(); que.pop();
        if(lock[u])
            continue;
        lock[u] = true;
        for(auto [v, w] : graph[u])
            maybe(v, dist[u] + w);
    }

    for(size_t u = 1; u <= n; u++)
        cout << dist[u] << ' ';
    cout << endl;

}
