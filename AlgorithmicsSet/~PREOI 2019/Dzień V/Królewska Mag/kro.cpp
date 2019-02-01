#ifdef XHOVA
#define _GLIBCXX_DEBUG
#endif // XHOVA
#include <bits/stdc++.h>

using namespace std;

struct edge { uint32_t i, u, v, w; };
struct b_edge { uint32_t i, v, w; };
struct a_edge { uint32_t v, w; };

struct disjoint_set
{
    uint32_t n;
    vector<uint32_t> parent, degree;
    disjoint_set(uint32_t _n) : n(_n), parent(n), degree(n)
        { iota(parent.begin(), parent.end(), 0); }
    uint32_t find(uint32_t v)
        { return v == parent[v] ? v : parent[v] = find(parent[v]); }
    void unite(uint32_t u, uint32_t v)
    {
        u = find(u); v = find(v);
        if(degree[u] > degree[v]) swap(u, v);
        if(degree[u] == degree[v]) degree[v]++;
        parent[u] = v;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<edge> E; E.reserve(m);
    vector<vector<b_edge>> G(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w; u--; v--;
        G[u].push_back({i, v, w});
        G[v].push_back({i, u, w});
        E.push_back({i, u, v, w});
    }
    auto graph_finder_cmp = [&](const b_edge& lhs, const b_edge& rhs) {
        return make_tuple(lhs.v, lhs.w, lhs.i) < make_tuple(rhs.v, rhs.w, rhs.i);
    };
    for(uint32_t u = 0; u < n; u++)
        sort(G[u].begin(), G[u].end(), graph_finder_cmp);
    sort(E.begin(), E.end(), [&](const edge& lhs, const edge& rhs) {
        return make_tuple(lhs.w, lhs.i, lhs.u, lhs.v) <
               make_tuple(rhs.w, rhs.i, rhs.u, rhs.v);
    });
    vector<bool> is_mst_edge(m);
    disjoint_set dset(n);
    uint32_t mst_weight = 0;
    for(auto e : E)
    {
        if(dset.find(e.u) != dset.find(e.v))
        {
            is_mst_edge[e.i] = true;
            dset.unite(e.u, e.v);
            mst_weight += e.w;
        }
    }

    vector<bool> vis(n);
    vector<uint32_t> depth(n);
    vector<vector<a_edge>> jump(n, vector<a_edge>(__lg(n) + 1, {-1u, 0}));
    queue<uint32_t> Q;
    Q.push(0); vis[0] = true;
    while(not Q.empty())
    {
        uint32_t u = Q.front(); Q.pop();
        for(auto e : G[u]) if(is_mst_edge[e.i] and not vis[e.v])
        {
            vis[e.v] = true;
            depth[e.v] = depth[u] + 1;
            jump[e.v][0] = {u, e.w};
            for(uint32_t j = 1; (1u << j) <= depth[e.v]; j++)
            {
                auto x = jump[e.v][j-1], y = jump[x.v][j-1];
                jump[e.v][j] = {y.v, max(x.w, y.w)};
            }
            Q.push(e.v);
        }
    }
    auto lca_path_max = [&](uint32_t u, uint32_t v)
    {
        uint32_t result = 0;
        if(depth[u] > depth[v])
            swap(u, v);
        for(uint32_t j = __lg(depth[v])+1; j --> 0; )
          if(depth[v] >= depth[u] + (1u << j))
        {
            result = max(result, jump[v][j].w);
            v = jump[v][j].v;
        }
        if(u == v) return result;
        for(uint32_t j = __lg(depth[v])+1; j --> 0; )
          if(depth[u] >= (1u << j) and jump[u][j].v != jump[v][j].v)
        {
            result = max(result, jump[u][j].w); u = jump[u][j].v;
            result = max(result, jump[v][j].w); v = jump[v][j].v;
        }
        result = max(result, jump[u][0].w);
        result = max(result, jump[v][0].w);
        return result;
    };
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        auto e = *lower_bound(G[u].begin(), G[u].end(),
                              b_edge{0, v, 0}, graph_finder_cmp);
        cout << mst_weight + e.w - lca_path_max(u, v) << "\n";
    }
}
