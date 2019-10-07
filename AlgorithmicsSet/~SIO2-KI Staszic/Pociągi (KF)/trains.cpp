#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<size_t>>;
struct edge { size_t v; uint64_t w; };
using wgraph_t = vector<vector<edge>>;

template<typename It>
void bring_maximums(It begin, It end, size_t k)
{
    k = min(k, size_t(end - begin));
    for(size_t i = 0; i < k; i++)
    {
        auto it = max_element(begin + i, end);
        iter_swap(it, begin + i);
    }
}

struct Tree
{
    graph_t graph;
    wgraph_t wgraph;
    vector<size_t> parent;
    vector<uint64_t> monopath, hipath;

    Tree(size_t n) : graph(n), wgraph(n), parent(n, SIZE_MAX), monopath(n), hipath(n)
    {
        for(size_t i = 0; i < n - 1; i++)
        {
            size_t u, v;
            cin >> u >> v; u--; v--;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        auto order = root(0);

        vector<uint> subtree(n, 1);
        for(auto u : order)
            for(auto v : graph[u]) if(v != parent[u])
                subtree[u] += subtree[v];

        for(size_t i = 1; i < n; i++)
        {
            size_t j = parent[i];
            auto w = (uint64_t)subtree[i] * (n - subtree[i]);
            wgraph[i].push_back({j, w});
            wgraph[j].push_back({i, w});
        }

        for(auto u : order)
            recompute(u);
    }


    void dfs_root(size_t u, vector<size_t>& order, size_t lock = SIZE_MAX)
    {
        for(auto v : graph[u])
            if(v != lock)
                parent[v] = u, dfs_root(v, order, u);
        order.push_back(u);
    }
    vector<size_t> root(size_t r)
    {
        vector<size_t> order;
        dfs_root(r, order);
        return order;
    }


    void recompute(size_t u)
    {
        monopath[u] = hipath[u] = 0;
        vector<uint64_t> val;
        val.reserve(wgraph[u].size() - 1);
        for(auto e : wgraph[u]) if(e.v != parent[u])
        {
            val.push_back(monopath[e.v] + e.w);
            monopath[u] = max(monopath[u], val.back());
            hipath[u] = max(hipath[u], hipath[e.v]);
        }
        hipath[u] = max(hipath[u], monopath[u]);
        bring_maximums(val.begin(), val.end(), 2);
        if(val.size() >= 2)
            hipath[u] = max(hipath[u], val[0] + val[1]);
    }


    uint64_t best_around_here(size_t u)
    {
        vector<uint64_t> val, wal;
        val.reserve(wgraph[u].size() - 1);
        wal.reserve(wgraph[u].size() - 1);
        for(auto e : wgraph[u]) if(e.v != parent[u])
            val.push_back(hipath[e.v]), wal.push_back(monopath[e.v] + e.w);

        const size_t m = val.size();

        uint64_t ret = hipath[u];

        array<array<uint64_t, 4>, 3> aux{}, aux1{};
        for(size_t i = 0; i < m; i++)
        {
            swap(aux, aux1);
            aux = aux1;
            for(size_t v = 0; v < 2; v++)
            {
                for(size_t w = 0; w < 3; w++)
                {
                    aux[v+1][w] = max(aux[v+1][w], aux1[v][w] + val[i]);
                    aux[v][w+1] = max(aux[v][w+1], aux1[v][w] + wal[i]);
                }
            }
        }
        ret = max(ret, aux[1][2]);

        return ret;
    }


    void dfs_root_travel(size_t u, uint64_t& result, size_t lock = SIZE_MAX)
    {
        result = max(result, best_around_here(u));

        vector<pair<uint64_t, size_t>> wal, hal;
        for(auto e : wgraph[u])
        {
            wal.emplace_back(monopath[e.v] + e.w, e.v);
            hal.emplace_back(hipath[e.v], e.v);
        }
        bring_maximums(wal.begin(), wal.end(), 3); wal.resize(3);
        bring_maximums(hal.begin(), hal.end(), 2); hal.resize(2);

        auto recompute_here_without = [&](size_t v) {
            monopath[u] = hipath[u] = 0;
            for(auto p : wal) if(p.second != v)
                monopath[u] = max(monopath[u], p.first);
            for(auto p : hal) if(p.second != v)
                hipath[u] = max(hipath[u], p.first);

            for(auto p : wal)
                for(auto q : wal)
                    if(p.second != v and q.second != v and p.second != q.second)
                        hipath[u] = max(hipath[u], p.first + q.first);
        };

        auto mu = monopath[u], hu = hipath[u];
        for(auto v : graph[u]) if(v != lock)
        {
            parent[u] = v;
            parent[v] = SIZE_MAX;
            auto mv = monopath[v], hv = hipath[v];

            recompute_here_without(v);
            recompute(v);

            dfs_root_travel(v, result, u);
            parent[v] = u;
            parent[u] = SIZE_MAX;
            monopath[v] = mv; hipath[v] = hv;
        }
        monopath[u] = mu; hipath[u] = hu;
    }
};


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    Tree T(n);

    uint64_t result = 0;
    T.dfs_root_travel(0, result);

    uint64_t acc = 0;
    for(size_t u = 0; u < n; u++)
        for(auto e : T.wgraph[u])
            acc += e.w;

    cout << (acc/2) - result;
}
