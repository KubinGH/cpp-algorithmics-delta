#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include <vector>
#include <bitset>
#include <algorithm>

// Kosaraju's algorithm.
// adhere to or change graph_t
// Call by kosaraju<N>{}(n, graph, rev_graph)

using std::size_t; using std::uint32_t;
using std::array; using std::vector; using std::bitset;
using std::reverse;

template<size_t N>
using graph_t = array<vector<uint32_t>, N>;

template<size_t N>
struct kosaraju
{
    bitset<N> vis;
    void marker_dfs(uint32_t u, graph_t<N>& graph, vector<uint32_t>& out)
    {
        for(uint32_t v : graph[u])
            if(not vis[v])
                vis[v] = true, marker_dfs(v, graph, out);
        out.push_back(u);
    }
    kosaraju() {}
    vector<vector<uint32_t>>
    operator() (uint32_t n, graph_t<N>& graph, graph_t<N>& rev_graph)
    {
        vector<uint32_t> order; order.reserve(n);
        vis.reset();
        for(uint32_t u = 0; u < n; u++)
            if(not vis[u])
                vis[u] = true, marker_dfs(u, graph, order);
        reverse(order.begin(), order.end());
        vis.reset();
        vector<vector<uint32_t>> result;
        for(uint32_t u : order)
        {
            if(not vis[u])
            {
                result.emplace_back();
                vis[u] = true;
                marker_dfs(u, rev_graph, result.back());
            }
        }
        return result;
    }
};

/*
7 10

1 2
2 1
2 5
5 4
1 4
3 2
3 7
7 6
6 3
6 5
*/
