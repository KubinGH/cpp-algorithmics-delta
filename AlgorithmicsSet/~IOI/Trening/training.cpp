// Niniejszym przyznaję się do skorzystania z omówienia tego zadania,
// w celu poznania obserwacji o tym, że żadna z krawędzi drzewa nie może być
// ,,pokryta'' przez więc niż jedną pozadrzewową.

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m;
    cin >> n >> m;

    vector<tuple<size_t, size_t, int>> edges(m);
    vector<vector<size_t>> tree(m);

    int total = 0;
    for(auto& [u, v, w] : edges)
    {
        cin >> u >> v >> w;
        u--; v--;
        if(not w)
            tree[u].push_back(v), tree[v].push_back(u);
        total += w;
    }

    vector<vector<size_t>> children(n);
    vector<size_t> parent(n), depth(n), order;
    vector<vector<bool>> ascend(n, vector<bool>(n)); // ascend[u][v] – v goes up to u
    order.reserve(n);

    function<void(size_t, size_t)> dfs_root = [&](size_t u, size_t lock) {
        for(auto v : tree[u])
            if(v != lock)
                parent[v] = u, children[u].push_back(v), depth[v] = depth[u] + 1, dfs_root(v, u);
        order.push_back(u);

        ascend[u][u] = true;
        for(auto v : children[u])
            for(size_t i = 0; i < n; i++)
                if(ascend[v][i])
                    ascend[u][i] = true;
    };

    dfs_root(0, SIZE_MAX);

    auto lca = [&](size_t u, size_t v) {
        if(depth[u] > depth[v]) swap(u, v);
        while(depth[u] < depth[v])
            v = parent[v];
        while(u != v)
            u = parent[u], v = parent[v];
        return u;
    };

    auto child_index = [&](size_t t, size_t v) {
        const auto& ch = children[t];
        return find(ch.begin(), ch.end(), v) - ch.begin();
    };
    auto get_real_children = [&](size_t r, size_t mask) {
        vector<size_t> out;
        for(size_t i = 0; i < children[r].size(); i++)
            if(mask >> i & 1)
                out.push_back(children[r][i]);
        return out;
    };

    vector<vector<tuple<size_t, size_t, int>>> options(n);
    for(auto [u, v, w] : edges)
        if(w)
    {
        auto a = lca(u, v);
        if(a == u) swap(u, v);
        if((depth[u]+depth[v]-2*depth[a]) % 2 == 0)
            options[a].emplace_back(u, v, w);
    }

    vector<vector<int>> best(n);
    for(auto r : order)
    {
        for(auto& [u, v, w] : options[r])
        {
            w += best[u].back() + (v == r ? 0 : best[v].back());
            auto doit = [&](size_t c) {
                while(parent[c] != r and c != r)
                {
                    size_t i = child_index(parent[c], c), k = children[parent[c]].size();
                    w += best[parent[c]][(1 << i) ^ ((1<<k)-1)];
                    c = parent[c];
                }
            };
            doit(u);
            doit(v);
        }

        best[r].resize(1 << children[r].size());

        for(size_t mask = 0; mask < best[r].size(); mask++)
        {
            auto real_children = get_real_children(r, mask);

            for(auto t : real_children)
                best[r][mask] += best[t].back();

            auto ascendant_of = [&](size_t u) {
                if(u == r) return u;
                for(auto t : real_children)
                    if(ascend[t][u])
                        return t;
                return SIZE_MAX;
            };

            for(auto [u, v, w] : options[r])
            {
                auto a = ascendant_of(u), b = ascendant_of(v);
                if(v == r) b = a;
                if(a == SIZE_MAX or b == SIZE_MAX)
                    continue;

                auto ia = child_index(r, a), ib = child_index(r, b);
                size_t mask1 = mask ^ ((1 << ia) | (1 << ib));
                best[r][mask] = max(best[r][mask], w + best[r][mask1]);
            }

        }
    }

    cout << total - best[0].back();
}
