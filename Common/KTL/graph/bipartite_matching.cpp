// Bipartite matching via Turbo Matching algorithm.
// Worst-case running time: O(|V|^2), but is a faster on average.
// Alternative in O(|E|^3/2): Dinic's Algorithm via a Flow Network
// Last revision: April 2019

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
    vector<size_t> vis, match;
    size_t timepoint = 1;
    static constexpr size_t NONMATCHED = SIZE_MAX;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n) {}

    void dfs_color(size_t u, vector<size_t>& out, bool c = true)
    {
        vis[u] = timepoint;
        if(c) out.push_back(u);
        for(auto v : graph[u])
            if(vis[v] < timepoint)
                dfs_color(v, out, not c);
    }

    vector<size_t> find_colored()
    {
        vector<size_t> colored;
        timepoint++;
        for(size_t u = 0; u < n; u++)
            if(vis[u] < timepoint)
                dfs_color(u, colored);
        return colored;
    }

    bool dfs_match(size_t u)
    {
        vis[u] = timepoint;
        for(auto v : graph[u])
        {
            if(match[v] == NONMATCHED)
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        for(auto v : graph[u])
        {
            if(vis[match[v]] < timepoint and dfs_match(match[v]))
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        return false;
    }

    vector<size_t> operator() (const vector<size_t>& colored)
    {
        fill(vis.begin(), vis.end(), timepoint);
        fill(match.begin(), match.end(), NONMATCHED);
        for(auto u : colored)
        {
            dfs_match(u);
            timepoint++;
        }
        return match;
    }
};
