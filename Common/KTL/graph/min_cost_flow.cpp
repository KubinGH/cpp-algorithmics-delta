// Min cost flow via Edmonds-Karp min-cost variation with SPFA.
//  (since I am not too sure about the Dijkstra implementation with potentials)
// `min_cost_max_flow` computes:
//  minimum cost (but at most `budget`) max flow (but at most `lim`)
// The algorithm stops when either of these would be broken if a path was taken
// Complexity: O(f VE)  (potentials achieve O(VE + f E log V), but bad constant)
// SPFA should have fine performance in general

// Last revision: April 2020

#pragma once

#include <algorithm>
#include <utility>
#include <cstddef>
#include <limits>
#include <vector>
#include <deque>

using std::min; using std::max; using std::fill;
using std::pair;
using std::vector; using std::deque;
using std::size_t;
using std::numeric_limits;

template<typename flow_t, typename cost_t>
struct min_cost_flow_network
{
    template<typename T>
    constexpr static T oo = numeric_limits<T>::max() - 0xF;

    struct edge
    {
        size_t s, t;
        flow_t cap; cost_t cost;
        bool rev; size_t rev_i;
    };

    size_t n, source, sink;
    vector<vector<edge>> graph;

    vector<cost_t> dist;
    vector<edge*> back;

    min_cost_flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t), graph(n), dist(n), back(n) {}

    void push(edge& e, int f) { e.cap -= f; graph[e.t][e.rev_i].cap += f; }
    int flow_at(edge& e) { return e.rev ? -e.cap : graph[e.t][e.rev_i].cap; }

    void add_edge(size_t s, size_t t, flow_t cap = +oo<flow_t>, cost_t cost = 0)
    {
        graph[s].push_back({s, t, cap, cost, false, graph[t].size()});
        graph[t].push_back({t, s, 0, -cost, true, graph[s].size() - 1});
    }

    bool spfa()
    {
        fill(dist.begin(), dist.end(), +oo<cost_t>);
        fill(back.begin(), back.end(), nullptr);
        deque<size_t> Q;
        Q.push_back(source); dist[source] = 0;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop_front();
            for(auto& e : graph[u])
            {
                if(e.cap and dist[u] + e.cost < dist[e.t])
                {
                    if(not Q.empty() and dist[e.t] <= dist[Q.front()])
                        Q.push_front(e.t);
                    else
                        Q.push_back(e.t);
                    dist[e.t] = dist[u] + e.cost;
                    back[e.t] = &e;
                }
            }
        }
        return dist[sink] != +oo<cost_t>;
    }

    pair<flow_t, cost_t> min_cost_max_flow(flow_t lim = +oo<flow_t>, cost_t budget = +oo<cost_t>)
    {
        flow_t flow = 0; cost_t total_cost = 0;
        while(spfa())
        {
            flow_t delta = +oo<flow_t>; cost_t cost = dist[sink];
            size_t u = sink;
            while(back[u])
                delta = min(delta, back[u]->cap), u = back[u]->s;

            delta = min(delta, lim - flow);
            if(cost > 0)
            {
                flow_t c = min((budget - total_cost) / cost, (cost_t)+oo<flow_t>);
                delta = min(delta, c);
            }

            if(not delta)
                break;

            u = sink;
            while(back[u])
                push(*back[u], delta), u = back[u]->s;

            flow += delta;
            total_cost += cost * delta;
        }
        return {flow, total_cost};
    }
};
