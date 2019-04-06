// Kosaraju's algorithm for finding strongly connected components.

// Last revision: April 2019

#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>
#include <utility>

using std::size_t;
using std::vector; using std::reverse;
using std::pair;
struct kosaraju
{
    using graph_t = vector<vector<size_t>>;
    size_t n;
    vector<bool> vis;

    kosaraju(size_t _n) : n(_n), vis(n) {}

    void marker_dfs(size_t u, const graph_t& graph, vector<uint32_t>& out)
    {
        vis[u] = true;
        for(size_t v : graph[u])
            if(not vis[v])
                marker_dfs(v, graph, out);
        out.push_back(u);
    }

    // Returns a list of strongly connected components, and
    // a list containing which SCC does a vertex belong to.
    pair<vector<vector<size_t>>, vector<size_t>>
    operator() (const graph_t& graph)
    {
        vector<size_t> order; order.reserve(n);
        fill(vis.begin(), vis.end(), false);
        for(size_t u = 0; u < n; u++)
            if(not vis[u])
                marker_dfs(u, graph, order);

        graph_t graph_T(n);
        for(size_t u = 0; u < n; u++)
            for(size_t v : graph[u])
                graph_T[v].push_back(u);

        fill(vis.begin(), vis.end(), false);
        reverse(order.begin(), order.end());
        vector<vector<size_t>> scc;
        vector<size_t> scc_idx(n);
        for(size_t u : order)
        {
            if(vis[u]) continue;
            scc.emplace_back();
            marker_dfs(u, graph_T, scc.back());
            for(auto i : scc.back())
                scc_idx[i] = scc.size() - 1;
        }
        return {scc, scc_idx};
    }
    
    // Construct a SCC graph.
    pair<vector<size_t>, graph_t>
    make_scc_graph(const graph_t& graph, const vector<vector<size_t>>& scc, const vector<size_t>& scc_idx)
    {
        fill(vis.begin(), vis.end(), false);
        graph_t scc_graph(scc.size());
        for(size_t i = 0; i < scc.size(); i++)
        {
            vis[i] = true;
            for(auto u : scc[i])
              for(auto v : graph[u])
                if(not vis[scc_idx[v]])
            {
                vis[scc_idx[v]] = true;
                scc_graph[i].push_back(scc_idx[v]);
            }
            vis[i] = false;
            for(auto e : scc_graph[i])
                vis[e] = false;
        }
        return {scc_idx, scc_graph};
    }
};