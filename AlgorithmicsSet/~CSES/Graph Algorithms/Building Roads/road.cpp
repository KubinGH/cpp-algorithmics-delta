#include <bits/stdc++.h>

using namespace std;

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
        graph[v].push_back(u);
    }

    vector<bool> vis(n+1);
    vector<vector<size_t>> comp;
    for(size_t s = 1; s <= n; s++) if(not vis[s])
    {
        function<void(size_t)> dfs = [&](size_t u) {
            if(vis[u])
                return;
            vis[u] = true;
            comp.back().push_back(u);
            for(auto v : graph[u])
                dfs(v);
        };
        comp.emplace_back();
        dfs(s);
    }

    cout << comp.size() - 1 << endl;
    for(size_t i = 0; i+1 < comp.size(); i++)
        cout << comp[i][0] << ' ' << comp[i+1][0] << '\n';
}
