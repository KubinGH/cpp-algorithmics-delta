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

    vector<bool> vis(n+1), color(n+1);
    bool ok = true;
    for(size_t s = 1; ok and s <= n; s++) if(not vis[s])
    {
        vector<size_t> stk;
        auto maybe = [&](size_t v, bool b) {
            if(not vis[v])
                vis[v] = true, color[v] = b, stk.push_back(v);
            else if(color[v] != b)
                ok = false;
        };
        maybe(s, 0);
        while(not stk.empty())
        {
            auto u = stk.back(); stk.pop_back();
            for(auto v : graph[u])
                maybe(v, not color[u]);
        }
    }

    if(ok)
    {
        for(size_t u = 1; u <= n; u++)
            cout << (int)color[u]+1 << ' ';
        cout << endl;
    }
    else
        cout << "IMPOSSIBLE" << endl;
}
