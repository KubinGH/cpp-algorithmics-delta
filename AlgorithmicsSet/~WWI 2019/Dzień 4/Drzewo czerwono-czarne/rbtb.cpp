#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<bool> color(n+1);
    for(size_t i = 1; i <= n; i++)
    {
        char c;
        cin >> c;
        color[i] = (c == '1');
    }

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<int> depth(n + 1);
    vector<vector<size_t>> jump(n + 1);

    function<void(size_t)> dfs_root = [&](size_t u) {
        for(auto v : graph[u]) if(v != jump[u][0])
        {
            depth[v] = depth[u] + 1;
            jump[v].push_back(u);
            for(size_t e = 1; (1 << e) <= depth[v]; e++)
                jump[v].push_back(jump[jump[v][e-1]][e-1]);
            dfs_root(v);
        }
    };

    jump[1].push_back(0);
    dfs_root(1);

    auto lca = [&](size_t u, size_t v) {
        if(depth[u] > depth[v])
            swap(u, v);
        for(size_t e = jump[v].size(); e --> 0; )
            if(depth[v] >= depth[u] + (1 << e))
                v = jump[v][e];
        if(u == v)
            return v;
        for(size_t e = jump[v].size(); e --> 0; )
            if(jump[u][e] != jump[v][e])
                u = jump[u][e], v = jump[v][e];
        return jump[v][0];
    };

    auto dist = [&](size_t u, size_t v) {
        return depth[u] + depth[v] - 2*depth[lca(u, v)];
    };

    function<int64_t(size_t, int, bool, size_t)> dfs_dist = [&](size_t u, int d, bool c, size_t lock) {
        int64_t r = c == color[u] ? d : 0;
        for(auto v : graph[u]) if(v != lock)
            r += dfs_dist(v, d + 1, c, u);
        return r;
    };

    while(q --> 0)
    {
        size_t t, u;
        cin >> t >> u;
        if(t == 1)
        {
            color[u] = not color[u];
        }
        else if(t == 2)
        {
            cout << dfs_dist(u, 0, color[u], 0) << '\n';
        }
    }
}
