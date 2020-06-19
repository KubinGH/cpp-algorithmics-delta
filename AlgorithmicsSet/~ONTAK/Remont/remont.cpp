#include <bits/stdc++.h>

using namespace std;

struct fenwick_tree
{
    size_t n;
    vector<int> F;

    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    void delta(size_t p, int v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }
    int get_prefix(size_t p) const
    {
        int r = 0;
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }
};

template<typename T>
struct sparse_table
{
    vector<vector<T>> A;

    template<typename It>
    sparse_table(It first, It last)
    {
        A.emplace_back();
        copy(first, last, back_inserter(A.back()));

        for(size_t k = 0; (2u << k) <= A[0].size(); k++)
        {
            A.emplace_back(A[0].size() - (2u << k) + 1);
            for(size_t i = 0; i + (2u << k) <= A[0].size(); i++)
                A[k+1][i] = min(A[k][i], A[k][i + (1u << k)]);
        }
    }

    const T& operator() (size_t i, size_t j) const
    {
        auto k = __lg(j - i);
        return min(A[k][i], A[k][j-(1u<<k)]);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    size_t n;
    cin >> n;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> preorder(n), postorder(n), depth(n), order;
    order.reserve(2*n+4);
    function<void(size_t, size_t)> dfs = [&](size_t u, size_t lock) {
        preorder[u] = order.size();
        order.push_back(u);
        for(auto v : graph[u])
            if(v != lock)
                depth[v] = depth[u] + 1, dfs(v, u), order.push_back(u);
        postorder[u] = order.size();
    };
    dfs(0, 0);

    vector<bool> exist(n, true);
    fenwick_tree F(order.size());
    auto push = [&](size_t u) {
        exist[u] = true;
        F.delta( preorder[u], -1);
        F.delta(postorder[u], +1);
    };
    auto pop = [&](size_t u) {
        exist[u] = false;
        F.delta( preorder[u], +1);
        F.delta(postorder[u], -1);
    };
    auto rootcount = [&](size_t u) {
        return F.get_prefix(preorder[u] + 1);
    };

    vector<pair<size_t, size_t>> vd(order.size());
    for(size_t i = 0; i < order.size(); i++)
        vd[i] = {depth[order[i]], order[i]};
    sparse_table<pair<size_t, size_t>> tab(vd.begin(), vd.end());

    size_t q;
    cin >> q;
    while(q --> 0)
    {
        char c;
        cin >> c;
        if(c == '?')
        {
            size_t u, v;
            cin >> u >> v; u--; v--;
            if(preorder[u] > preorder[v])
                swap(u, v);
            size_t a = tab(preorder[u], postorder[v]).second;
            auto x = rootcount(u) + rootcount(v) - 2 * rootcount(a) + (not exist[a]);
            cout << (x ? "NIE" : "TAK") << '\n';
        }
        else if(c == '+' or c == '-')
        {
            size_t v;
            cin >> v; v--;
            if(exist[v]) pop(v);
            else         push(v);
        }
    }
}
