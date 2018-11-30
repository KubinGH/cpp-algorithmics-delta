#include <bits/stdc++.h>

using namespace std;

vector<vector<uint32_t>> graph;
vector<uint32_t> parent, preorder, order, low;
uint32_t dfs_time = 0;
vector<bool> vis;

void dfs_root(uint32_t u)
{
    preorder[u] = dfs_time++;
    low[u] = preorder[u];
    for(uint32_t v : graph[u])
    {
        if(vis[v] and preorder[v] < preorder[u])
            low[u] = min(low[u], preorder[v]);
        if(not vis[v])
        {
            parent[v] = u;
            vis[v] = true;
            dfs_root(v);
            low[u] = min(low[u], low[v]);
        }
    }
    order.push_back(u);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, root;
    cin >> n >> m >> root; root--;
    graph.resize(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    parent.resize(n);
    preorder.resize(n); vis.resize(n); low.resize(n);
    vis[root] = true; parent[root] = -1u;
    dfs_root(root);
    vector<uint32_t> art(n), arttree(n);
    reverse(order.begin(), order.end());
    for(uint32_t u : order)
    {
        if(u == root) continue;
        art[u] += arttree[u];
        for(uint32_t v : graph[u])
        {
            if(parent[v] != u) continue;
            arttree[v] += arttree[u];
            if(low[v] >= preorder[u])
                arttree[v]++;
        }
    }
    for(uint32_t u = 0; u < n; u++)
        cout << art[u] << " ";
}
