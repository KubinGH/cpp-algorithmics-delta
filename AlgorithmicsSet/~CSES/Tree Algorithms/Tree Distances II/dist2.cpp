#include <bits/stdc++.h>

using namespace std;

vector<vector<size_t>> graph;
vector<int> sub;
vector<int64_t> result, sumdist;

void dfs_root(size_t u, size_t parent = 0)
{
    for(auto v : graph[u])
        if(v != parent)
            dfs_root(v, u), sub[u] += sub[v], sumdist[u] += sumdist[v] + sub[v];
}

void dfs_move(size_t u, size_t lock = 0)
{
    result[u] = sumdist[u];
    for(auto v : graph[u]) if(v != lock)
    {
        auto su = sub[u], sv = sub[v]; auto sdu = sumdist[u], sdv = sumdist[v];
        sumdist[u] -= sumdist[v] + sub[v]; sub[u] -= sub[v];
        sub[v] += sub[u]; sumdist[v] += sumdist[u] + sub[u];
        dfs_move(v, u);
        sub[u] = su; sub[v] = sv;
        sumdist[u] = sdu; sumdist[v] = sdv;
    }
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

    sub.resize(n + 1, 1); result.resize(n + 1); sumdist.resize(n + 1); sub[0] = 0;
    dfs_root(1); dfs_move(1);

    for(size_t u = 1; u <= n; u++)
        cout << result[u] << ' ';
    cout << endl;
}
