#include <bits/stdc++.h>

using namespace std;

const uint32_t MAX_V = 1 << 19, MAX_E = 1 << 20, MAX_W = 1 << 27;

struct edge { uint32_t v; uint64_t w; };

struct kosaraju
{
    const vector<vector<edge>>& graph;
    uint32_t n;
    vector<bool> vis;
    vector<vector<edge>> rev_graph;
    kosaraju(const vector<vector<edge>>& _graph)
        : graph(_graph), n(graph.size()), vis(n), rev_graph(n)
    {
        for(uint32_t u = 0; u < n; u++)
            for(auto e : graph[u])
                rev_graph[e.v].push_back({u, e.w});
    }
    void marker_dfs(uint32_t u, const vector<vector<edge>>& c_graph, vector<uint32_t>& out)
    {
        for(auto e : c_graph[u])
            if(not vis[e.v])
                vis[e.v] = true, marker_dfs(e.v, c_graph, out);
        out.push_back(u);
    }
    vector<vector<uint32_t>> find_scc()
    {
        vis.assign(vis.size(), false);
        vector<uint32_t> order; order.reserve(n);
        for(uint32_t u = 0; u < n; u++)
            if(not vis[u])
                vis[u] = true, marker_dfs(u, graph, order);
        reverse(order.begin(), order.end());
        vis.assign(vis.size(), false);
        vector<vector<uint32_t>> scc;
        for(uint32_t u : order)
        {
            if(vis[u])
                continue;
            scc.emplace_back();
            vis[u] = true;
            marker_dfs(u, rev_graph, scc.back());
        }
        return scc;
    }
};

int main()
{

    vector<uint64_t> n_chi; n_chi.reserve(1<<16);
    while(n_chi.size()*(n_chi.size()+1)/2 < MAX_W)
        n_chi.push_back(n_chi.size()*(n_chi.size() + 1)/2);
    vector<uint64_t> n_chi_sums(n_chi.size());
    partial_sum(n_chi.begin(), n_chi.end(), n_chi_sums.begin());
    auto chi = [&](uint64_t x) {
        if(x == 0) return 0llu;
        auto it = upper_bound(n_chi.begin(), n_chi.end(), x); it--;
        uint64_t n = it - n_chi.begin();
        return (n+1)*x - n_chi_sums[n];
    };
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<edge>> graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; uint64_t w;
        cin >> u >> v >> w; u--; v--;
        graph[u].push_back({v, w});
    }
    auto scc = kosaraju{graph}.find_scc();
    vector<uint32_t> scc_index(n);
    for(uint32_t s = 0; s < scc.size(); s++)
        for(uint32_t u : scc[s])
            scc_index[u] = s;
    vector<vector<edge>> scc_graph(scc.size());
    vector<uint64_t> scc_values(scc.size());
    vector<uint32_t> ingoing(scc.size());
    for(uint32_t s = 0; s < scc.size(); s++)
    {
        for(uint32_t u : scc[s])
        {
            for(auto e : graph[u])
            {
                if(scc_index[u] == scc_index[e.v])
                    scc_values[s] += chi(e.w);
                else
                {
                    scc_graph[scc_index[u]].push_back({scc_index[e.v], e.w});
                    ingoing[scc_index[e.v]]++;
                }
            }
        }
    }
    vector<uint32_t> topo; topo.reserve(scc.size());
    for(uint32_t s = 0; s < scc.size(); s++)
        if(ingoing[s] == 0)
            topo.push_back(s);
    uint32_t start;
    cin >> start; start--;
    vector<bool> reachable(scc.size());
    vector<uint64_t> scc_result(scc.size());
    uint64_t result = 0;
    for(uint32_t t = 0; t < topo.size(); t++)
    {
        uint32_t u = topo[t];
        for(uint32_t v : scc[u])
            if(v == start)
                reachable[u] = true;
        scc_result[u] += scc_values[u];
        for(auto e : scc_graph[u])
        {
            if(reachable[u])
            {
                reachable[e.v] = true;
                scc_result[e.v] = max(scc_result[e.v], scc_result[u] + e.w);
            }
            if(--ingoing[e.v] == 0)
                topo.push_back(e.v);
        }
        if(reachable[u])
            result = max(result, scc_result[u]);
    }
    cout << result;
}
