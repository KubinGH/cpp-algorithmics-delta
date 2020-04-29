// Maximum flow using Dinic's algorithm.
// Enable scaling by setting the base to a value greater than 1.
// Complexity: min(O(f E), O(V^2 E))
//  with scaling: O(VE log C), but higher constant factor
// Notes:
// - Seems like changing the scale base improves the performance by up to 25-40%
//   Some tests on VN SPOJ/LOJ imply that 22 is more or less optimal
// - Performance improves by 10-30% after replacing vectors with arrays
//   (remember to remove initializers from the constructor)
// - Switching the edges around (transpose) may improve performance for special tests.
// - An additional DFS that removes vertices not reachable from the sink in the
//   network transpose could improve performance.
// - IMPORTANT (sometimes): do not break from the augment loop, return instead! (20% boost)
// -
// Last revision: April 2020, tested on multiple tasks and quite good for a Dinic

#pragma once

#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>
#include <queue>

using std::min; using std::max; using std::__lg; using std::fill;
using std::vector; using std::queue;
using std::size_t;
using std::numeric_limits;

template<typename flow_t, flow_t ScaleBase = 0>
struct flow_network
{
    constexpr static auto oo = numeric_limits<flow_t>::max() - 0xF;

    struct edge
    {
        size_t s, t;
        flow_t cap; bool rev;
        size_t rev_i;
    };

    size_t n, source, sink;
    vector<vector<edge>> graph;

    vector<int> dist;
    vector<size_t> curr_edge;

    flow_t bound = 1;

    flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t), graph(n), dist(n), curr_edge(n) {}

    void push(edge& e, flow_t f) { e.cap -= f; graph[e.t][e.rev_i].cap += f; }
    flow_t flow_at(edge& e) { return graph[e.t][e.rev_i].cap; }

    void add_edge(size_t s, size_t t, flow_t cap = +oo)
    {
        graph[s].push_back({s, t, cap, false, graph[t].size()});
        graph[t].push_back({t, s, 0, true, graph[s].size() - 1});
        if(ScaleBase) bound = max(bound, cap);
    }

    bool bfs()
    {
        fill(dist.begin(), dist.end(), -1);
        queue<size_t> Q;
        Q.push(source); dist[source] = 0;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for(auto& e : graph[u])
                if(e.cap >= bound and dist[e.t] == -1)
                    Q.push(e.t), dist[e.t] = dist[u] + 1;
        }
        if(ScaleBase and dist[sink] == -1 and bound > 1)
        {
            bound /= ScaleBase;
            if(not bound) bound = 1;
            return bfs();
        }
        return dist[sink] != -1;
    }

    flow_t augment_dfs(size_t u, flow_t lim)
    {
        if(u == sink or not lim)
            return lim;
        flow_t delta = 0;
        if(dist[u] < dist[sink])
          for(size_t& j = curr_edge[u]; j < graph[u].size(); j++)
        {
            auto& e = graph[u][j]; const auto v = e.t;
            if(e.cap and dist[v] == dist[u] + 1)
            {
                auto x = augment_dfs(v, min(lim - delta, e.cap));
                push(e, x); delta += x;
            }
            if(delta == lim)
                return lim;
        }
        if(not delta)
            dist[u] = -1;
        return delta;
    }

    flow_t max_flow()
    {
        flow_t flow = 0;
        while(bfs())
        {
            fill(curr_edge.begin(), curr_edge.end(), 0);
            flow += augment_dfs(source, +oo);
        }
        return flow;
    }
};
