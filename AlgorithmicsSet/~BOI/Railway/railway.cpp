#include <bits/stdc++.h>

using namespace std;

constexpr size_t JUMP = 17;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<size_t, size_t>>> graph(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }

    vector<size_t> parent(n + 1), depth(n + 1), parent_idx(n + 1);
    vector<array<size_t, JUMP>> jump(n + 1);

    function<void(size_t)> dfs = [&](size_t u) {
        jump[u][0] = parent[u];
        for(size_t j = 0; j+1 < JUMP; j++)
            jump[u][j+1] = jump[jump[u][j]][j];
        for(auto [v, i] : graph[u]) if(v != parent[u])
        {
            depth[v] = depth[u] + 1;
            parent[v] = u;
            parent_idx[v] = i;
            dfs(v);
        }
    };
    dfs(1);

    auto lca = [&](size_t u, size_t v) {
        if(depth[u] > depth[v])
            swap(u, v);
        for(size_t j = JUMP; j --> 0; )
            if(depth[v] - depth[u] >= (1u << j))
                v = jump[v][j];
        if(u == v)
            return u;
        for(size_t j = JUMP; j --> 0; )
            if(jump[u][j] != jump[v][j])
                u = jump[u][j], v = jump[v][j];
        return parent[u];
    };

    vector<vector<size_t>> pushes(n + 1), pops(n + 1);
    for(size_t i = 0; i < m; i++)
    {
        size_t s;
        cin >> s;
        vector<size_t> vert(s);
        for(auto& u : vert)
            cin >> u, pushes[u].push_back(i);
        auto a = vert[0];
        for(auto u : vert)
            a = lca(a, u);
        pops[a].push_back(i);
    }

    vector<size_t> resulto;
    function<void(size_t, set<size_t>&)> solve = [&](size_t u, set<size_t>& active) {
        for(auto i : pushes[u])
            active.insert(i);

        for(auto [v, _] : graph[u]) if(v != parent[u])
        {
            set<size_t> sub;
            solve(v, sub);
            if(active.size() < sub.size())
                active.swap(sub);
            for(auto i : sub)
                active.insert(i);
        }

        for(auto i : pops[u])
            active.erase(i);

        if(active.size() >= k)
            resulto.push_back(parent_idx[u]);
    };
    set<size_t> tmp;
    solve(1, tmp);

    sort(resulto.begin(), resulto.end());
    cout << resulto.size() << endl;
    for(auto i : resulto)
        cout << i << ' ';
    cout << endl;
}
