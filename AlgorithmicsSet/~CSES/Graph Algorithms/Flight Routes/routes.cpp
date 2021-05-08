#include <bits/stdc++.h>

using namespace std;

constexpr size_t K = 10;
constexpr int64_t oo = INT64_MAX/3 - 0xD;
template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<size_t, int>>> graph(n+1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }

    vector<array<int64_t, K>> dist(n+1);
    for(size_t u = 2; u <= n; u++)
        dist[u].fill(+oo);

    vector<size_t> lock(n+1);
    min_heap<pair<int64_t, size_t>> que;

    que.emplace(0, 1);
    while(not que.empty())
    {
        auto [d, u] = que.top(); que.pop();
        if(lock[u] >= k)
            continue;
        dist[u][lock[u]++] = d;
        for(auto [v, w] : graph[u])
            que.emplace(d + w, v);
    }

    for(size_t i = 0; i < k; i++)
        cout << dist[n][i] << ' ';
    cout << endl;
}
