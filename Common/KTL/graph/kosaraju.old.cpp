// Kosaraju's algorithm.
// Call by kosaraju<N>{}(n, graph, rev_graph)

// Last revision: July 2018

#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>
#include <bitset>
#include <algorithm>

using std::size_t; using std::uint32_t;
using std::vector; using std::bitset;
using std::reverse;

template<size_t N, typename graph_t>
struct kosaraju
{
    bitset<N> vis;
    void marker_dfs(uint32_t u, const graph_t& graph, vector<uint32_t>& out)
    {
        for(uint32_t v : graph[u])
            if(not vis[v])
                vis[v] = true, marker_dfs(v, graph, out);
        out.push_back(u);
    }
    kosaraju() {}
    vector<vector<uint32_t>>
    operator() (uint32_t n, const graph_t& graph, const graph_t& rev_graph)
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

/*
#include <bits/stdc++.h>
using namespace std;
int main()
{
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<uint32_t>> G(n), Gt(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        Gt[v].push_back(u);
    }
    for(auto C : kosaraju<999999, vector<vector<uint32_t>>>{}(n, G, Gt))
    {
        for(auto u : C)
            cout << u+1 << " ";
        cout << endl;
    }
}
*/
