#include <bits/stdc++.h>

using namespace std;

struct kosaraju
{
    const vector<vector<uint32_t>>& graph;
    vector<vector<uint32_t>> rev_graph;
    vector<bool> vis;
    kosaraju(const vector<vector<uint32_t>>& _graph) : graph(_graph)
    {
        const uint32_t n = graph.size();
        rev_graph.resize(n);
        for(uint32_t u = 0; u < n; u++)
            for(uint32_t v : graph[u])
                rev_graph[v].push_back(u);
        vis.resize(n);
    }
    void marker_dfs(uint32_t u, const vector<vector<uint32_t>>& s_graph, vector<uint32_t>& out)
    {
        for(uint32_t v : s_graph[u])
            if(not vis[v])
                vis[v] = true, marker_dfs(v, s_graph, out);
        out.push_back(u);
    }
    vector<vector<uint32_t>> find_scc()
    {
        const uint32_t n = graph.size();
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
            if(vis[u]) continue;
            vis[u] = true;
            scc.emplace_back();
            marker_dfs(u, rev_graph, scc.back());
        }
        return scc;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<uint32_t> gain(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> gain[i];
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }


    vector<vector<uint32_t>> scc = kosaraju(graph).find_scc();
    const uint32_t s = scc.size();
    vector<uint32_t> scc_value(s), parent_scc(n);
    for(uint32_t i = 0; i < s; i++)
        for(uint32_t u : scc[i])
            scc_value[i] += gain[u], parent_scc[u] = i;

    vector<vector<uint32_t>> scc_graph(s);
    vector<uint32_t> ingoing(s);
    vector<bool> this_has_conn(s);
    for(uint32_t i = 0; i < s; i++)
    {
        this_has_conn[i] = true;
        for(uint32_t u : scc[i])
          for(uint32_t v : graph[u])
        {
            if(not this_has_conn[parent_scc[v]])
            {
                uint32_t j = parent_scc[v];
                scc_graph[i].push_back(j);
                this_has_conn[j] = true;
                ingoing[j]++;
            }
        }
        for(uint32_t j : scc_graph[i])
            this_has_conn[j] = false;
        this_has_conn[i] = false;
    }


    vector<uint32_t> topo; topo.reserve(s);
    for(uint32_t i = 0; i < s; i++)
        if(ingoing[i] == 0)
            topo.push_back(i);
    vector<uint32_t> result(s);
    uint32_t total_result = 0;
    for(uint32_t t = 0; t < topo.size(); t++)
    {
        uint32_t i = topo[t];
        result[i] += scc_value[i];
        total_result = max(total_result, result[i]);
        for(uint32_t j : scc_graph[i])
        {
            result[j] = max(result[j], result[i]);
            if(--ingoing[j] == 0)
                topo.push_back(j);
        }
    }
    cout << total_result;
}
