#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<size_t>>;

struct edge { size_t v; uint64_t w; }

using wgraph_t = vector<vector<edge>>;

void dfs_root(size_t u, const graph_t& graph, vector<size_t>& parent, vector<size_t>& order, size_t lock = SIZE_MAX)
{
    for(auto v : graph[u])
        if(v != lock)
            parent[v] = u, dfs_root(v, graph, parent, order, u);
    order.push_back(u);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    graph_t graph(n);
    for(size_t i = 0; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> order, parent(n); order.reserve(n);
    dfs_root(0, graph, parent, order);

    vector<uint> subtree(n, 1);
    for(auto u : order)
        for(auto v : graph[u]) if(v != parent[u])
            subtree[u] += subtree[v];

    wgraph_t wgraph(n);
    for(size_t i = 1; i < n; i++)
    {
        size_t j = parent[i];
        auto w = (uint64_t)subtree[i] * (n - subtree[i]);
        wgraph[i].emplace_back(j, w);
        wgraph[j].emplace_back(i, w);
    }

    vector<uint64_t> monopath(n), dipath(n);

    for(auto u : order)
    {
        vector<uint64_t> val;
        val.reserve(wgraph[u].size() - 1);
        for(auto e : wgraph[u]) if(e.v != u)
            val.push_back(monopath[e.v] + e.w);
        nth_element()
    }
}
