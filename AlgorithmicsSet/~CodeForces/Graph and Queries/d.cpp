#include <bits/stdc++.h>

using namespace std;

const size_t JUMPS = 20;

struct disjoint_set
{
    vector<size_t> repr, rank;

    disjoint_set(size_t n) : repr(n), rank(n)
    {
        for(size_t i = 0; i < n; i++)
            repr[i] = rank[i] = i;
        shuffle(rank.begin(), rank.end(), mt19937{});
    }

    size_t find(size_t u)
    {
        return u == repr[u] ? u : repr[u] = find(repr[u]);
    }

    bool unite(size_t u, size_t v)
    {
        if((u = find(u)) == (v = find(v)))
            return false;
        if(rank[u] > rank[v])
            swap(u, v);
        repr[v] = u;
        return true;
    }
};

pair<vector<size_t>, vector<size_t>> make_tree(const size_t n, const vector<pair<size_t, size_t>>& edges)
{
    vector<size_t> parent(n+1), where(n+1), lim(n+1);
    disjoint_set dset(n+1);

    lim[0] = SIZE_MAX;
    for(size_t i = 0; i <= n; i++)
        where[i] = i;

    for(size_t i = 0; i < edges.size(); i++)
    {
        auto [u, v] = edges[edges.size()-i-1];
        size_t a = where[dset.find(u)], b = where[dset.find(v)];
        if(dset.unite(u, v))
        {
            where[dset.find(u)] = parent[a] = parent[b] = parent.size();
            parent.push_back(0);
            lim.push_back(i + 1);
        }
    }
    for(size_t u = 1; u < parent.size(); u++)
        if(not parent[u])
            parent[u] = parent.size();
    parent.emplace_back();
    lim.push_back(edges.size() + 1);
    return {parent, lim};
}

tuple<vector<size_t>, vector<size_t>, vector<array<size_t, JUMPS>>> process_tree(const vector<size_t>& parent, size_t root)
{
    const size_t n = parent.size();
    vector<array<size_t, JUMPS>> jump(n);
    vector<size_t> preorder(n), postorder(n);
    vector<vector<size_t>> children(n);
    for(size_t u = 0; u < n; u++)
        children[parent[u]].push_back(u);

    size_t watch = 0;
    function<void(size_t)> dfs = [&](size_t u) {
        preorder[u] = watch++;
        jump[u][0] = parent[u];
        for(size_t i = 0; i+1 < JUMPS; i++)
            jump[u][i+1] = jump[jump[u][i]][i];
        for(auto v : children[u])
            dfs(v);
        postorder[u] = watch;
    };
    dfs(root);

    return {preorder, postorder, jump};
}

struct segment_tree
{
    size_t w;
    vector<pair<int, size_t>> values;

    segment_tree(size_t n) : w(1 << __lg(2*n - 1)), values(2*w) {}

    void set(size_t p, pair<int, size_t> v)
    {
        values[p += w] = v;
        while(p)
            p /= 2, values[p] = max(values[2*p], values[2*p+1]);
    }

    pair<int, size_t> get(size_t l, size_t r) const
    {
        pair<int, size_t> result = {0, 0};
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) result = max(result, values[l++]);
            if(r % 2) result = max(result, values[--r]);
        }
        return result;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<int> val(n+1);
    for(size_t u = 1; u <= n; u++)
        cin >> val[u];

    vector<tuple<size_t, size_t, size_t>> labeled_edges(m);
    for(size_t i = 0; i < m; i++)
    {
        auto& [j, u, v] = labeled_edges[i];
        cin >> u >> v; j = i;
    }

    vector<pair<char, size_t>> queries(q);
    vector<size_t> pop_at(m, SIZE_MAX);
    for(size_t i = 0; i < q; i++)
    {
        int t; size_t v;
        cin >> t >> v;
        if(t == 1)
            queries[i] = {'!', v};
        else if(t == 2)
            queries[i] = {'-', v-1}, pop_at[v-1] = i;
    }

    sort(labeled_edges.begin(), labeled_edges.end(), [&](const auto& lhs, const auto& rhs) {
        return pop_at[get<0>(lhs)] < pop_at[get<0>(rhs)];
    });
    vector<pair<size_t, size_t>> edges(m);
    for(size_t i = 0; i < m; i++)
        edges[i] = {get<1>(labeled_edges[i]), get<2>(labeled_edges[i])};

    auto [parent, lim] = make_tree(n, edges);
    auto [preorder, postorder, jump] = process_tree(parent, parent.size() - 1);

    auto component_jump = [&](size_t u, size_t e) {
        for(size_t k = JUMPS; k --> 0; )
            if(lim[jump[u][k]] <= e)
                u = jump[u][k];
        return u;
    };

    segment_tree tree(parent.size());
    for(size_t u = 1; u <= n; u++)
        tree.set(preorder[u], {val[u], u});

    size_t e = edges.size();
    for(auto [t, j] : queries)
    {
        if(t == '!')
        {
            auto a = component_jump(j, e);
            auto [w, u] = tree.get(preorder[a], postorder[a]);
            tree.set(preorder[u], {0, u});
            cout << w << '\n';
        }
        else if(t == '-')
            e--;
    }
}
