#include <bits/stdc++.h>

using namespace std;

void marker_dfs(size_t u, const vector<vector<size_t>>& G, vector<bool>& vis, vector<size_t>& out)
{
    if(vis[u])
        return;
    vis[u] = true;
    for(auto v : G[u])
        marker_dfs(v, G, vis, out);
    out.push_back(u);
}
void dfs(size_t u, const vector<vector<size_t>>& G, vector<bool>& vis)
{
    if(vis[u])
        return;
    vis[u] = true;
    for(auto v : G[u])
        dfs(v, G, vis);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n), hparg(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        hparg[v].push_back(u);
    }

    vector<bool> vis(n);
    vector<size_t> order;

    for(size_t u = 0; u < n; u++)
        marker_dfs(u, graph, vis, order);

    fill(vis.begin(), vis.end(), false);
    reverse(order.begin(), order.end());

    vector<size_t> vert;
    dfs(order[0], hparg, vis);

    auto it = find(vis.begin(), vis.end(), false);
    if(it == vis.end())
    {
        cout << "YES" << endl;
        return 0;
    }
    size_t missingno = it - vis.begin();

    fill(vis.begin(), vis.end(), false);
    dfs(missingno, graph, vis);
    if(not vis[order[0]])
    {
        cout << "NO" << endl << missingno+1 << ' ' << order[0]+1 << endl;
        return 0;
    }
    fill(vis.begin(), vis.end(), false);
    dfs(order[0], graph, vis);
    if(not vis[missingno])
    {
        cout << "NO" << endl << order[0]+1 << ' ' << missingno+1 << endl;
        return 0;
    }

    assert(false);
}
