#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> vis(n);
    size_t watch = 1;
    function<void(size_t)> dfs = [&](size_t u) {
        if(vis[u]) return;
        vis[u] = watch;
        for(auto v : graph[u])
            dfs(v);
    };

    for(size_t u = 0; u < n; u++)
        if(not vis[u])
            dfs(u), watch++;

    for(size_t i = 0; i < q; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        cout << "NT"[vis[u] == vis[v]] << '\n';
    }
}
