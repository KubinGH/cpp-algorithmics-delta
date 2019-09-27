#include <bits/stdc++.h>

using namespace std;

struct kosaraju
{
    size_t n;
    const vector<vector<size_t>>& graph;
    vector<bool> vis;
    vector<vector<size_t>> t_graph;

    kosaraju(const vector<vector<size_t>>& _graph)
        : n(_graph.size()), graph(_graph), vis(n), t_graph(n)
    {
        for(size_t u = 0; u < n; u++)
            for(auto v : graph[u])
                t_graph[v].push_back(u);
    }

    void marker_dfs(size_t u, vector<size_t>& out, const vector<vector<size_t>>& G)
    {
        vis[u] = true;
        for(auto v : G[u])
            if(not vis[v])
                marker_dfs(v, out, G);
        out.push_back(u);
    }

    pair<vector<size_t>, vector<vector<size_t>>> operator() ()
    {
        vis.assign(n, false);
        vector<size_t> order; order.reserve(n);
        for(size_t u = 0; u < n; u++)
            if(not vis[u])
                marker_dfs(u, order, graph);

        vis.assign(n, false);
        reverse(order.begin(), order.end());
        vector<size_t> scc_idx(n);
        vector<vector<size_t>> scc;
        for(auto u : order)
        {
            if(vis[u])
                continue;
            scc.emplace_back();
            marker_dfs(u, scc.back(), t_graph);
            for(auto v : scc.back())
                scc_idx[v] = scc.size() - 1;
        }

        return {scc_idx, scc};
    }

    vector<vector<size_t>> make_scc_graph(const vector<size_t>& scc_idx, const vector<vector<size_t>>& scc)
    {
        size_t s = scc.size();
        vector<vector<size_t>> scc_graph(s);

        vis.assign(n, false);
        for(size_t i = 0; i < s; i++)
        {
            vis[i] = true;
            for(size_t u : scc[i])
                for(auto v : graph[u])
                    if(not vis[scc_idx[v]])
                        vis[scc_idx[v]] = true, scc_graph[i].push_back(scc_idx[v]);
            vis[i] = false;
            for(auto j : scc_graph[i])
                vis[j] = false;
        }

        return scc_graph;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }

    kosaraju kos(graph);
    vector<size_t> scc_idx;
    vector<vector<size_t>> scc;
    tie(scc_idx, scc) = kos();
    auto scc_graph = kos.make_scc_graph(scc_idx, scc);

    auto s = scc.size();

    if(s == 1)
    {
        cout << 0;
        return 0;
    }

    vector<size_t> scc_in(s), scc_out(s);

    vector<vector<size_t>> u_scc_graph = scc_graph;
    for(size_t i = 0; i < s; i++)
        for(auto j : scc_graph[i])
            scc_out[i]++, scc_in[j]++, u_scc_graph[j].push_back(i);

    size_t in0 = 0, out0 = 0;
    for(size_t i = 0; i < s; i++)
    {
        if(scc_in [i] == 0)  in0++;
        if(scc_out[i] == 0) out0++;
    }
    cout << max(in0, out0);
}
