// Bipartite matching via Hopcroft-Karp algorithm.
// Worst-case running time: O(|E| sqrt(|V|)), but is faster on average.
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
    vector<bool> vis;
    vector<size_t> match;

    bipartite_matching(const graph_t& _graph)
        : graph(_graph), n(graph.size()), vis(n), match(n, SIZE_MAX) {}

    void dfs_color(size_t u, vector<size_t>& out, bool c = true)
    {
        vis[u] = true;
        if(c) out.push_back(u);
        for(auto v : graph[u])
            if(not vis[v])
                dfs_color(v, out, not c);
    }

    vector<size_t> find_colored()
    {
        vector<size_t> colored;
        colored.reserve(n);
        fill(vis.begin(), vis.end(), false);
        for(size_t u = 0; u < n; u++)
            if(not vis[u])
                dfs_color(u, colored);
        return colored;
    }

    bool dfs_match(size_t u)
    {
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
            if(not vis[match[v]] and dfs_match(match[v]))
            {
                match[u] = v; match[v] = u;
                return true;
            }
        }
        return false;
    }

    vector<size_t> operator() (const vector<size_t>& colored)
    {
        fill(match.begin(), match.end(), SIZE_MAX);

        bool any = true;
        while(any)
        {
            any = false;
            fill(vis.begin(), vis.end(), false);
            for(auto u : colored)
                if(match[u] == SIZE_MAX and dfs_match(u))
                    any = true;
        }
        return match;
    }

    vector<size_t> operator() ()
    {
        auto colored = find_colored();
        return operator() (colored);
    }
};
