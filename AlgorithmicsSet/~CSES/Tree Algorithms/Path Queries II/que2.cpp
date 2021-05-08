#include <bits/stdc++.h>
#include <ktl/util/fastio.cpp>
#define cin ucin
#define cout ucout
#define endl '\n'

using namespace std;

template<typename T, typename Monoid>
struct segment_tree
{
    size_t w;
    vector<T> values;
    const T identity;
    Monoid f;

    segment_tree(size_t n, const T id, Monoid _f)
        : w(1 << __lg(2*n - 1)), values(2*w), identity(id), f(_f) {}

    template<typename It>
    void build(It first, It last)
    {
        fill(values.begin(), values.end(), identity);
        copy(first, last, values.begin() + w);
        for(size_t i = w; i --> 1; )
            values[i] = f(values[2*i], values[2*i + 1]);
    }

    void set(size_t p, T v)
    {
        values[p += w] = v;
        while(p /= 2)
            values[p] = f(values[2*p], values[2*p + 1]);
    }

    T get(size_t l, size_t r) const
    {
        T a = identity, b = identity;
        for(l += w, r += w; l < r; l /= 2, r /= 2)
        {
            if(l % 2) a = f(a, values[l++]);
            if(r % 2) b = f(values[--r], b);
        }
        return f(a, b);
    }
};
template<typename T, typename Monoid>
segment_tree(size_t, T, Monoid) -> segment_tree<T, Monoid>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int> value(n + 1);
    for(size_t u = 1; u <= n; u++)
        cin >> value[u];

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> parent(n + 1), depth(n + 1), sub(n + 1);
    function<void(size_t)> dfs_root = [&](size_t u) {
        sub[u] = 1;
        if(auto it = find(graph[u].begin(), graph[u].end(), parent[u]); it != graph[u].end())
            graph[u].erase(it);
        for(auto v : graph[u])
            parent[v] = u, depth[v] = depth[u] + 1, dfs_root(v), sub[v] += sub[u];
        if(not graph[u].empty())
        {
            auto it = max_element(graph[u].begin(), graph[u].end(), [&](size_t lhs, size_t rhs) {
                return sub[lhs] < sub[rhs];
            });
            iter_swap(it, graph[u].begin());
        }
    }; dfs_root(1);

    size_t watch = 0;
    vector<size_t> preorder(n + 1), postorder(n + 1), hld_parent(n + 1), of_preorder(n);
    function<void(size_t)> dfs_hld = [&](size_t u) {
        of_preorder[preorder[u] = watch++] = u;
        for(size_t i = 0; i < graph[u].size(); i++)
        {
            auto v = graph[u][i];
            hld_parent[v] = u == 1 or i ? v : hld_parent[u];
            dfs_hld(v);
        }
        postorder[u] = watch;
    }; dfs_hld(1);

    auto hld = [&](size_t u, size_t v, auto f) {
        while(hld_parent[u] != hld_parent[v])
        {
            if(depth[hld_parent[u]] > depth[hld_parent[v]]) swap(u, v);
            f(preorder[hld_parent[v]], preorder[v]);
            v = parent[hld_parent[v]];
        }
        if(depth[u] > depth[v]) swap(u, v);
        f(preorder[u], preorder[v]);
    };
    auto lca = [&](size_t u, size_t v) {
        size_t r = 0;
        hld(u, v, [&](size_t a, size_t) {
            r = a;
        });
        return of_preorder[r];
    };

    segment_tree tree(n, 0, [](int a, int b) { return max(a, b); });
    vector<int> preorder_value(n);
    for(size_t u = 1; u <= n; u++)
        preorder_value[preorder[u]] = value[u];
    tree.build(preorder_value.begin(), preorder_value.end());

    while(q --> 0)
    {
        char t;
        cin >> t;

        if(t == '1')
        {
            size_t u; int x;
            cin >> u >> x;
            tree.set(preorder[u], value[u] = x);
        }
        else if(t == '2')
        {
            size_t u, v;
            cin >> u >> v;
            int r = 0;
            hld(u, v, [&](size_t a, size_t b) {
                r = max(r, tree.get(a, b+1));
            });
            cout << r << ' ';
        }
    }
    cout << endl;

}
