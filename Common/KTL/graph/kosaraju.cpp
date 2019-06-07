// Kosaraju's algorithm for finding strongly connected components.
// Example of the graph algorithm scheme: object that is constructed on the graph, operator() performs the algorithm.
// Any memory allocation is done in the constructor. The graph is kept in a const-reference.
// Last revision: April 2019

#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple> 

using std::size_t;
using std::vector; using std::reverse;
using std::pair; using std::tie;

struct kosaraju
{
    using graph_t = vector<vector<size_t>>;

    const graph_t& graph;
    size_t n;
    vector<bool> vis;

    kosaraju(const graph_t& _graph) : graph(_graph), n(graph.size()), vis(n) {}

    void marker_dfs(size_t u, const graph_t& G, vector<size_t>& out)
    {
        vis[u] = true;
        for(size_t v : G[u])
            if(not vis[v])
                marker_dfs(v, G, out);
        out.push_back(u);
    }

    // Returns a list of strongly connected components, and
    // a list containing which SCC does a vertex belong to.
    pair<vector<vector<size_t>>, vector<size_t>>
    operator() ()
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
    graph_t make_scc_graph(const vector<vector<size_t>>& scc, const vector<size_t>& scc_idx)
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
        return scc_graph;
    }
    
    graph_t make_scc_graph()
    {
        vector<vector<size_t>> scc;
        vector<size_t> scc_idx;
        tie(scc, scc_idx) = operator() ();
        return make_scc_graph(scc, scc_idx);
    }
};
