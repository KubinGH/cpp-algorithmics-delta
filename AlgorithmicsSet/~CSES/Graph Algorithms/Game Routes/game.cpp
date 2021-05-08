#include <bits/stdc++.h>

using namespace std;

constexpr uint mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n+1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    vector<bool> vis(n+1);
    vector<uint> cnt(n+1, 0);
    cnt[n] = 1;

    function<void(size_t)> dfs = [&](size_t u) {
        if(vis[u])
            return;
        vis[u] = true;
        for(auto v : graph[u])
        {
            dfs(v);
            cnt[u] += cnt[v];
            cnt[u] %= mod;
        }
    };

    dfs(1);
    cout << cnt[1] << endl;
}
