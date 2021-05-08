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
    }

    vector<bool> vis(n+1);
    vector<size_t> back(n+1);
    vector<int> mx(n+1, INT_MIN);
    mx[n] = 0;

    function<void(size_t)> dfs = [&](size_t u) {
        if(vis[u])
            return;
        vis[u] = true;
        for(auto v : graph[u])
        {
            dfs(v);
            if(mx[v] != INT_MIN and mx[u] < mx[v] + 1)
                mx[u] = mx[v] + 1, back[u] = v;
        }
    };

    dfs(1);

    if(back[1])
    {
        vector<size_t> path;
        size_t u = 1;
        while(u)
            path.push_back(u), u = back[u];
        cout << path.size() << endl;
        for(auto v : path)
            cout << v << ' ';
        cout << endl;
    }
    else
        cout << "IMPOSSIBLE" << endl;
}
