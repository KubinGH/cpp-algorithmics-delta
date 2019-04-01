#include <bits/stdc++.h>

using namespace std;

int main()
{
#ifndef XHOVA
    ifstream cin("factory.in");
    ofstream cout("factory.out");
#endif
    uint32_t n;
    cin >> n;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[v].push_back(u);
    }
    vector<bool> vis(n);
    function<void(uint32_t)> dfs = [&](uint32_t u) {
        vis[u] = true;
        for(uint32_t v : graph[u])
            if(not vis[v])
                dfs(v);
    };
    for(uint32_t i = 0; i < n; i++)
    {
        fill(vis.begin(), vis.end(), false);
        dfs(i);
        if(not count(vis.begin(), vis.end(), false))
        {
            cout << i+1;
            return 0;
        }
    }
    cout << "-1";
}
