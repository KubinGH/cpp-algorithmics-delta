#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<size_t, size_t>>> graph;
vector<bool> vis, stk;
vector<size_t> preorder, low;
vector<bool> is_bridge;

size_t watch = 0;

void dfs(size_t u, size_t p = SIZE_MAX)
{
    vis[u] = stk[u] = true;
    low[u] = preorder[u] = watch++;
    for(auto [v, i] : graph[u])
    {
        if(v == p)
            {}
        else if(not vis[v])
        {
            dfs(v, u);
            if(preorder[u] < low[v])
                is_bridge[i] = true;
            low[u] = min(low[u], low[v]);
        }
        else if(vis[v] and stk[v])
            low[u] = min(low[u], preorder[v]);
    }
    stk[u] = false;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph.resize(n);
    vis.resize(n); stk.resize(n);
    preorder.resize(n); low.resize(n);
    is_bridge.resize(m);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;

        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }

    dfs(0);

    size_t cnt = 0;
    for(size_t i = 0; i < m; i++)
        cnt += is_bridge[i];
    cout << cnt << '\n';
    for(size_t i = 0; i < m; i++)
        if(is_bridge[i])
            cout << i+1 << ' ';
}
