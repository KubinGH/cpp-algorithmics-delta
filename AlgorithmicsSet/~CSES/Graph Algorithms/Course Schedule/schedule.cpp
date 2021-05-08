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
    for(size_t u = 1; u <= n; u++)
        graph[0].push_back(u);

    vector<bool> vis(n+1), stk(n+1);
    vector<size_t> order;
    bool bad = false;
    function<void(size_t)> dfs = [&](size_t u) {
        vis[u] = stk[u] = true;
        for(auto v : graph[u])
        {
            if(not vis[v])
                dfs(v);
            else if(stk[v])
                bad = true;
        }
        stk[u] = false;
        order.push_back(u);
    };
    dfs(0);
    order.pop_back();
    reverse(order.begin(), order.end());

    if(not bad)
    {
        for(auto u : order)
            cout << u << ' ';
        cout << endl;
    }
    else
        cout << "IMPOSSIBLE" << endl;
}
