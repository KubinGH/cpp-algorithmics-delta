#include <bits/stdc++.h>

using namespace std;

struct kosaraju
{
    const vector<vector<uint32_t>>& graph;
    uint32_t n;
    vector<bool> vis;
    vector<vector<uint32_t>> graphT;
    kosaraju(const vector<vector<uint32_t>>& _graph)
        : graph(_graph), n(graph.size()), vis(n), graphT(n)
    {
        for(uint32_t u = 0; u < n; u++)
            for(uint32_t v : graph[u])
                graphT[v].push_back(u);
    }
    void marker_dfs(uint32_t u, const vector<vector<uint32_t>>& sgraph, vector<uint32_t>& out)
    {
        for(uint32_t v : sgraph[u])
            if(not vis[v])
                vis[v] = true, marker_dfs(v, sgraph, out);
        out.push_back(u);
    }
    vector<vector<uint32_t>> find_scc()
    {
        fill(vis.begin(), vis.end(), false);
        vector<uint32_t> order; order.reserve(n);
        for(uint32_t u = 0; u < n; u++)
            if(not vis[u])
                vis[u] = true, marker_dfs(u, graph, order);
        reverse(order.begin(), order.end());
        fill(vis.begin(), vis.end(), false);
        vector<vector<uint32_t>> scc;
        for(uint32_t u : order)
        {
            if(vis[u])
                continue;
            scc.emplace_back();
            vis[u] = true;
            marker_dfs(u, graphT, scc.back());
        }
        return scc;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }
    auto scc = kosaraju(graph).find_scc(); uint32_t s = scc.size();
    vector<uint32_t> scc_index(n);
    for(uint32_t i = 0; i < s; i++)
        for(uint32_t u : scc[i])
            scc_index[u] = i;
    vector<vector<uint32_t>> scc_graph(s), weak_scc_graph(s);
    vector<uint32_t> ingoing(s), outgoing(s);
    vector<bool> scc_used(s);
    for(uint32_t i = 0; i < s; i++)
    {
        scc_used[i] = true;
        for(uint32_t u : scc[i])
          for(uint32_t v : graph[u])
        {
            uint32_t j = scc_index[v];
            if(not scc_used[j])
            {
                scc_used[j] = true;
                scc_graph[i].push_back(j);
                outgoing[i]++; ingoing[j]++;
                weak_scc_graph[i].push_back(j);
                weak_scc_graph[j].push_back(i);
            }
        }
        for(uint32_t j : scc_graph[i])
            scc_used[j] = false;
        scc_used[i] = false;
    }
    uint32_t p = 0, q = 0;
    for(uint32_t i = 0; i < s; i++)
    {
        if(not ingoing[i])
            p++;
        if(not outgoing[i])
            q++;
    }
    cout << (s == 1 ? 0 : max(p, q));
}
