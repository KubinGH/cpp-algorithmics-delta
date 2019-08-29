#include <bits/stdc++.h>

// -*- ktl/graph/dag_dominators.cpp -*-

#include <algorithm>
#include <vector>
#include <cstdint>
#include <functional>

using std::vector; using std::pair;
using std::function;
using std::swap;
using std::size_t;

using graph_t = vector<vector<size_t>>;

vector<size_t> src_topological(const graph_t& graph, size_t source)
{
    const size_t n = graph.size();
    vector<size_t> indegree(n);
    vector<size_t> V; vector<bool> vis(n);
    function<void(size_t)> dfs_explore = [&](size_t u) {
        vis[u] = true;
        V.push_back(u);
        for(size_t v : graph[u])
            if(not vis[v])
                dfs_explore(v);
    };
    dfs_explore(source);
    for(size_t u : V)
        for(size_t v : graph[u])
            indegree[v]++;
    vector<size_t> T; T.reserve(V.size());
    T.push_back(source);
    for(size_t t = 0; t < T.size(); t++)
    {
        size_t u = T[t];
        for(size_t v : graph[u])
            if(--indegree[v] == 0)
                T.push_back(v);
    }
    return T;
}

pair<vector<size_t>, vector<size_t>> dag_dominators(const graph_t& graph, size_t root)
{
    const size_t n = graph.size();
    vector<size_t> idom(n, SIZE_MAX), id_depth(n, 0);
    vector<vector<size_t>> id_jump(n);

    auto lca = [&](size_t u, size_t v) {
        if(id_depth[u] > id_depth[v]) swap(u, v);
        for(size_t k = id_jump[v].size(); k --> 0; )
            if(id_depth[v] >= id_depth[u] + (1u << k))
                v = id_jump[v][k];
        if(u == v) return v;
        for(size_t k = id_jump[v].size(); k --> 0; )
            if(k < id_jump[u].size() and id_jump[u][k] != id_jump[v][k])
                u = id_jump[u][k], v = id_jump[v][k];
        return id_jump[u][0];
    };

    auto T = src_topological(graph, root);

    graph_t ingraph(n);
    for(size_t u : T)
        for(size_t v : graph[u])
            ingraph[v].push_back(u);

    for(size_t u : T)
    {
        if(ingraph[u].empty())
            continue;
        size_t a = ingraph[u][0];
        for(size_t v : ingraph[u])
            a = lca(a, v);
        idom[u] = a;
        id_jump[u].push_back(a);
        for(size_t k = 1; true; k++)
        {
            size_t v = id_jump[u][k-1];
            if(id_jump[v].size() >= k)
                id_jump[u].push_back(id_jump[v][k-1]);
            else
                break;
        }
        id_depth[u] = id_depth[a] + 1;
    }

    return {idom, T};
}

// -$- ktl/graph/dag_dominators.cpp -$-


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
