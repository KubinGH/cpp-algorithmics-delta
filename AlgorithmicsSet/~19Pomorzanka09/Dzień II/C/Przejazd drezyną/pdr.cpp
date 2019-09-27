#include <bits/stdc++.h>

using namespace std;

vector<vector<size_t>> graph;
vector<bool> vis;
int timer = 1;

void dfs(size_t u)
{
    vis[u] = true;
    for(auto v : graph[u])
        if(not vis[v])
            dfs(v);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph.resize(n); vis.resize(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<vector<bool>> reach;
    for(size_t u = 0; u < n; u++)
    {
        fill(vis.begin(), vis.end(), false);
        dfs(u);
        reach.emplace_back(vis);
    }

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        cout << reach[u][v];
    }
}
