// Bipartite matching via a variation of Turbo Matching.
// Worst-case running time: O(|V||E|), but is much faster on average.
// Last revision: April 2019 (minor: February 2021)

#pragma once

#include <vector>
#include <cstddef>
#include <cstdint>

using std::vector; using std::size_t;

struct bipartite_matching
{
    using graph_t = vector<vector<size_t>>;

    const graph_t& graph;
    size_t n;
    vector<bool> vis;
    vector<size_t> match;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n, SIZE_MAX) {}

    bool dfs_match(size_t u)
    {
        if(vis[u])
            return false;
        vis[u] = true;
        for(auto v : graph[u])
        {
            if(match[v] == SIZE_MAX)
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        for(auto v : graph[u])
        {
            if(dfs_match(match[v]))
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        return false;
    }

    vector<size_t> operator() ()
    {
        fill(match.begin(), match.end(), SIZE_MAX);

        bool any = true;
        while(any)
        {
            any = false;
            fill(vis.begin(), vis.end(), false);
            for(size_t u = 0; u < n; u++)
                if(match[u] == SIZE_MAX and dfs_match(u))
                    any = true;
        }
        return match;
    }
};
