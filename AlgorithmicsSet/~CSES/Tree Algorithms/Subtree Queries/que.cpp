#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree
{
    size_t n;
    vector<int64_t> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    void delta(size_t p, int64_t v)
    {
        for(p++; p <= n; p += p & -p)
            F[p] += v;
    }

    int64_t get_prefix(size_t p) const
    {
        int64_t r = 0;
        for(; p; p &= p - 1)
            r += F[p];
        return r;
    }

    int64_t get(size_t l, size_t r) const { return get_prefix(r) - get_prefix(l); }
};

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

    size_t watch = 0;
    vector<size_t> preorder(n + 1), postorder(n + 1);
    function<void(size_t, size_t)> dfs = [&](size_t u, size_t parent) {
        preorder[u] = watch++;
        for(auto v : graph[u])
            if(v != parent)
                dfs(v, u);
        postorder[u] = watch;
    };
    dfs(1, 0);

    fenwick_tree tree(n);
    auto update = [&](size_t u, int a) {
        tree.delta(preorder[u], a - value[u]); value[u] = a;
    };
    for(size_t u = 1; u <= n; u++)
        { int a = value[u]; value[u] = 0; update(u, a); }

    while(q --> 0)
    {
        char t;
        cin >> t;
        if(t == '1')
        {
            size_t u; int a;
            cin >> u >> a;
            update(u, a);
        }
        else if(t == '2')
        {
            size_t u;
            cin >> u;
            cout << tree.get(preorder[u], postorder[u]) << '\n';
        }
    }
}
