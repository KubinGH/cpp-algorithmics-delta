#include <bits/stdc++.h>

using namespace std;

constexpr size_t JUMP = 18;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> parent(n + 1);
    vector<uint> depth(n + 1);
    vector<array<size_t, JUMP>> jump(n + 1);

    function<void(size_t)> dfs = [&](size_t u) {
        jump[u][0] = parent[u];
        for(size_t j = 0; j+1 < JUMP; j++)
            jump[u][j+1] = jump[jump[u][j]][j];
        for(auto v : graph[u]) if(v != parent[u])
            parent[v] = u, depth[v] = depth[u] + 1, dfs(v);
    }; dfs(1);

    auto jump_k = [&](size_t u, uint k) {
        for(size_t j = 0; j < JUMP; j++)
            if(k >> j & 1)
                u = jump[u][j];
        return u;
    };

    auto lca = [&](size_t u, size_t v) {
        if(depth[u] > depth[v])
            swap(u, v);
        if(u == (v = jump_k(v, depth[v] - depth[u])))
            return u;
        for(size_t j = JUMP; j --> 0; )
            if(jump[u][j] != jump[v][j])
                u = jump[u][j], v = jump[v][j];
        return parent[u];
    };

    vector<int> result(n + 1), delta(n + 1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        delta[u]++; delta[v]++;
        auto a = lca(u, v);
        delta[a] -= 2; result[a]++;
    }

    function<int(size_t)> dfs_delta = [&](size_t u) {
        int s = delta[u];
        for(auto v : graph[u])
            if(v != parent[u])
                s += dfs_delta(v);
        result[u] += s;
        return s;
    };
    dfs_delta(1);

    for(size_t u = 1; u <= n; u++)
        cout << result[u] << ' ';
    cout << endl;
}
