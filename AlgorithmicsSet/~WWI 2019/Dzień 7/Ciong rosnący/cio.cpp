#include <bits/stdc++.h>
#include <ktl/graph/dag_dominators.cpp>

using namespace std;

struct fenwick_tree
{
    size_t n;
    vector<pair<uint, int>> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1) {}

    static constexpr size_t lsb(size_t x) { return x & -x; }

    pair<uint, int> get_prefix(size_t p)
    {
        pair<uint, int> r = {0, INT_MIN};
        while(p)
            r = max(r, F[p]), p -= lsb(p);
        return r;
    }

    void delta(size_t p, pair<uint, int> v)
    {
        p++;
        while(p <= n)
            F[p] = max(F[p], v), p += lsb(p);
    }
};

struct dynamic_lis
{
    fenwick_tree F;

    dynamic_lis(size_t n) : F(n) {}

    pair<uint, int> end_with(uint x)
    {
        return F.get_prefix(x + 1);
    }
    void push_back(uint x, int i)
    {
        return F.delta(x, {end_with(x).first + 1, i});
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<uint> a(n+1);
    for(size_t i = 1; i <= n; i++)
        cin >> a[i];

    auto result_prefix = [&]() {
        dynamic_lis Lmin(n+1), Lmax(n+1);
        vector<vector<size_t>> graph(n+1);

        vector<size_t> b(n+1);
        for(size_t i = 0; i <= n; i++)
            b[a[i]] = i;

        for(size_t i = 1; i <= n; i++)
        {
            size_t j1 = b[-Lmin.end_with(a[i]).second], j2 = b[Lmax.end_with(a[i]).second];
            graph[j1].push_back(i);
            graph[j2].push_back(i);
            Lmin.push_back(a[i], -a[i]);
            Lmax.push_back(a[i], a[i]);
        }

        auto dom = dag_dominators(graph, 0);
        auto idom = dom.first; auto topo = dom.second;
        vector<size_t> depth(n+1, -1);
        for(auto u : topo)
        {
            assert(not u or idom[u] <= n);
            if(u) depth[u] = depth[idom[u]] + 1;
        }
        depth.erase(depth.begin(), depth.begin() + 1);
        return depth;
    };

    auto r1 = result_prefix();
    reverse(a.begin()+1, a.end());
    for(size_t i = 1; i <= n; i++)
        a[i] = (n+1) - a[i];
    auto r2 = result_prefix();
    reverse(r2.begin(), r2.end());

    for(size_t i = 0; i < n; i++)
        cout << r1[i] + r2[i] << " ";
    cout << endl;
}
