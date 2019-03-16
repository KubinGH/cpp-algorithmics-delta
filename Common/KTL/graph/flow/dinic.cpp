// Dinic's max-flow algorithm.
// Complexity: O(|V|^2 |E|); with unit weights: O(min(|V|^(2/3), |E|^(1/2)) * |E|)

#pragma once

#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "flow-graph.hpp"

using namespace std;

namespace dinic
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
        capacity_t max_flow = 0;

        bool done = false;

        vector<uint32_t> dist(n), next_edge(n);
        do {
            done = true;

            queue<uint32_t> tovis;
            fill(dist.begin(), dist.end(), -1u);
            fill(next_edge.begin(), next_edge.end(), 0);
            dist[source] = 0; tovis.push(source);
            while(not tovis.empty())
            {
                uint32_t u = tovis.front(); tovis.pop();
                for(uint32_t i = 0; i < F[u].size(); i++)
                {
                    auto e = F[u][i];
                    if(e.c and dist[e.v] == -1u)
                    {
                        dist[e.v] = dist[u] + 1;
                        tovis.push(e.v);
                    }
                }
            }

            function<capacity_t(uint32_t, capacity_t)> dfs_extend = [&](uint32_t u, capacity_t lim) {
                if(u == sink)
                    return lim;
                capacity_t r = 0;
                for(uint32_t& i = next_edge[u]; i < F[u].size() and lim; i++)
                {
                    auto& e = F[u][i];
                    if(dist[e.v] == dist[u] + 1)
                    {
                        capacity_t x = dfs_extend(e.v, min(lim, e.c));
                        if(x)
                        {
                            e.c -= x;
                            F[e.v][e.rev_i].c += x;
                        }
                        lim -= x;
                        r += x;
                    }
                }
                return r;
            };
            max_flow += dfs_extend(source, numeric_limits<capacity_t>::max());
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
