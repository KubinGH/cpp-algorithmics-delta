#include <bits/stdc++.h>

using namespace std;

vector<vector<size_t>> graph;
vector<int> result;
vector<array<pair<int, size_t>, 2>> path;

void path_update(size_t u, int d, size_t v)
{
    pair c(d, v);
    if(c >= path[u][0])
        path[u][1] = path[u][0], path[u][0] = c;
    else if(c > path[u][1])
        path[u][1] = c;
}

void dfs_root(size_t u, size_t parent = 0)
{
    for(auto v : graph[u])
        if(v != parent)
            dfs_root(v, u), path_update(u, path[v][0].first + 1, v);
}

void dfs_move(size_t u, size_t lock = 0)
{
    result[u] = max(result[u], path[u][0].first);
    for(auto v : graph[u])
        if(v != lock)
            path_update(v, 1 + (path[u][0].second != v ? path[u][0].first : path[u][1].first), u), dfs_move(v, u);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    graph.resize(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    result.resize(n + 1); path.resize(n + 1);
    dfs_root(1); dfs_move(1);

    for(size_t u = 1; u <= n; u++)
        cout << result[u] << ' ';
    cout << endl;
}
