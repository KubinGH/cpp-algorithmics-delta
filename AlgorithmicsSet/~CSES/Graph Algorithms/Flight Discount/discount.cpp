#include <bits/stdc++.h>

using namespace std;

constexpr int64_t oo = INT64_MAX/3 - 0xD;
template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<size_t, int64_t>>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int w;
        cin >> u >> v >> w; u--; v--;
        graph[u].emplace_back(v, w);
    }

    auto no = [&](size_t i) {
        return i >= n ? i - n : i;
    };

    vector<int64_t> dist(2*n, +oo);
    vector<bool> lock(2*n);
    min_heap<pair<int64_t, size_t>> que;
    auto maybe = [&](size_t u, int64_t d) {
        if(d < dist[u])
            lock[u] = false, que.emplace(dist[u] = d, u);
    };
    maybe(0, 0);
    while(not que.empty())
    {
        auto u = que.top().second; que.pop();
        if(lock[u])
            continue;
        lock[u] = true;
        for(auto [v, w] : graph[no(u)])
        {
            if(u >= n) v += n;
            else maybe(v+n, dist[u] + w/2);
            maybe(v, dist[u] + w);
        }
    }

    cout << min(dist[n-1], dist[2*n-1]) << endl;
}
