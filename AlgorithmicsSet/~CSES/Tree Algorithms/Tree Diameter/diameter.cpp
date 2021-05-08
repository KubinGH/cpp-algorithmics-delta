#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto bfs = [&](size_t source) {
        vector<int> dist(n + 1, -1);
        vector<size_t> tovis;
        auto maybe = [&](size_t u, size_t d) {
            if(dist[u] == -1)
                dist[u] = d, tovis.push_back(u);
        };
        maybe(source, 0);
        while(not tovis.empty())
        {
            auto u = tovis.back(); tovis.pop_back();
            for(auto v : graph[u])
                maybe(v, dist[u] + 1);
        }
        return dist;
    };

    auto dist_1 = bfs(1);
    auto u = max_element(dist_1.begin(), dist_1.end()) - dist_1.begin();
    auto dist_u = bfs(u);
    auto v = max_element(dist_u.begin(), dist_u.end()) - dist_u.begin();
    cout << dist_u[v] << endl;
}
