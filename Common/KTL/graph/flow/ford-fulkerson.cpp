// Ford-Fulkerson max flow method. Uses plain DFS to find the paths.
// Largely similar to (and worse than) the Edmonds-Karp, which uses BFS.
// Exists for demonstration purposes.
// Complexity: O(f |E|), where f is the max flow.
// Last revision: March 2019

#pragma once

#include <utility>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>
#include "flow-graph.hpp"

using namespace std;

using std::fill; using std::make_pair; using std::min;
using std::vector; using std::pair; using std::stack;
using std::size_t;
using std::numeric_limits;

namespace ford_fulkerson
{
    using namespace flow;
    pair<capacity_t, graph> find_max_flow(const graph& G, size_t source, size_t sink)
    {
        const size_t n = G.size();
        bnd_graph F(n);
        for(uint32_t u = 0; u < n; u++)
            for(auto e : G[u])
        {
            F[u].emplace_back(u, e.v, e.c, F[e.v].size());
            F[e.v].emplace_back(e.v, u, 0, F[u].size() - 1);
        }
        bool done = false;

        capacity_t max_flow = 0;
        vector<pair<uint32_t, uint32_t>> prev(n, {-1u, -1u});
        vector<bool> vis(n);

        do {
            done = true;

            stack<uint32_t> tovis;
            fill(prev.begin(), prev.end(), make_pair(-1u, -1u));
            fill(vis.begin(), vis.end(), false);

            vis[source] = true; tovis.push(source);
            while(not tovis.empty())
            {
                uint32_t u = tovis.top(); tovis.pop();
                for(uint32_t i = 0; i < F[u].size(); i++)
                {
                    auto e = F[u][i];
                    if(e.c and not vis[e.v])
                    {
                        vis[e.v] = true;
                        prev[e.v] = {u, i};
                        tovis.push(e.v);
                    }
                }
            }
            if(vis[sink])
            {
                vector<uint32_t> path;
                {
                    uint32_t u = sink;
                    while(u != source)
                    {
                        path.push_back(u);
                        u = prev[u].first;
                    }
                    path.push_back(u);
                }
                reverse(path.begin(), path.end());
                capacity_t minim = numeric_limits<capacity_t>::max();
                for(uint32_t i = 1; i < path.size(); i++)
                {
                    uint32_t u = path[i-1], v = path[i];
                    auto e = F[u][prev[v].second];
                    minim = min(minim, e.c);
                }
                max_flow += minim;
                for(uint32_t i = 1; i < path.size(); i++)
                {
                    uint32_t u = path[i-1], v = path[i];
                    auto& e = F[u][prev[v].second];
                    e.c -= minim;
                    F[e.v][e.rev_i].c += minim;
                }
                done = false;
            }
        } while(not done);

        graph R(n);
        for(uint32_t u = 0; u < n; u++)
            for(auto e : F[u])
        {
            R[u].emplace_back(e.v, F[e.v][e.rev_i].c);
        }

        return {max_flow, R};
    }
}
