#include <bits/stdc++.h>

using namespace std;

constexpr size_t JUMP = 18;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<size_t> parent(n + 1);
    vector<vector<size_t>> children(n + 1);
    for(size_t i = 2; i <= n; i++)
        cin >> parent[i], children[parent[i]].push_back(i);

    vector<uint> depth(n + 1);
    vector<array<size_t, JUMP>> jump(n + 1);

    function<void(size_t)> dfs = [&](size_t u) {
        jump[u][0] = parent[u];
        for(size_t j = 0; j+1 < JUMP; j++)
            jump[u][j+1] = jump[jump[u][j]][j];
        for(auto v : children[u])
            depth[v] = depth[u] + 1, dfs(v);
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

    while(q --> 0)
    {
        size_t u, v;
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}
