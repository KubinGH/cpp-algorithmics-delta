// -*- ktl/graph/min_cost_flow.cpp -*-

// Min cost flow via Edmonds-Karp min-cost variation with SPFA.
//  (since I am not too sure about the Dijkstra implementation with potentials)
// `min_cost_max_flow` computes:
//  minimum cost (but at most `budget`) max flow (but at most `lim`)
// The algorithm stops when either of these would be broken if a path was taken
// Complexity: O(f VE)  (potentials achieve O(VE + f E log V), but bad constant)
// SPFA should have fine performance in general

// Last revision: April 2020

#include <algorithm>
#include <utility>
#include <cstddef>
#include <limits>
#include <vector>
#include <queue>

using std::min; using std::max; using std::fill;
using std::pair;
using std::vector; using std::queue;
using std::size_t;
using std::numeric_limits;

template<typename flow_t, typename cost_t>
struct min_cost_flow_network
{
    template<typename T>
    constexpr static auto oo = numeric_limits<T>::max() - 0xF;

    struct edge
    {
        size_t s, t;
        int cap, cost;
        bool rev; size_t rev_i;
    };

    size_t n, source, sink;
    vector<vector<edge>> graph;

    vector<int> dist;
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
        queue<size_t> Q;
        Q.push(source); dist[source] = 0;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for(auto& e : graph[u])
                if(e.cap and dist[u] + e.cost < dist[e.t])
                    Q.push(e.t), dist[e.t] = dist[u] + e.cost, back[e.t] = &e;
        }
        return dist[sink] != +oo<cost_t>;
    }

    pair<flow_t, cost_t> min_cost_max_flow(flow_t lim = +oo<flow_t>, cost_t budget = +oo<cost_t>)
    {
        flow_t flow = 0; cost_t total_cost = 0;
        while(spfa())
        {
            auto delta = +oo<flow_t>; auto cost = dist[sink];
            size_t u = sink;
            while(back[u])
                delta = min(delta, back[u]->cap), u = back[u]->s;

            delta = min(delta, lim - flow);
            if(cost > 0)
                delta = min(delta, (budget - total_cost) / cost);

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

// -$- ktl/graph/min_cost_flow.cpp -$-

#include <iostream>
#include <map>

using namespace std;


struct segment { int a, b, c; size_t i; };

int main()
{
    size_t n; int k;
    cin >> n >> k;

    map<int, int> remap;
    vector<segment> A(n);
    for(size_t i = 0; i < n; i++)
    {
        auto& [a, b, c, j] = A[i];
        cin >> a >> b >> c, b += a-1;
        remap[a]; remap[b];
        j = i;
    }

    int m = 0;
    for(auto& [_, v] : remap)
        v = m++;

    for(size_t u = 0; u < n; u++)
    {
        auto& [a, b, _, __] = A[u];
        a = remap[a]; b = remap[b];
    }

    sort(A.begin(), A.end(), [](const segment& lhs, const segment& rhs) {
        return tie(lhs.a, lhs.b) < tie(rhs.a, rhs.b);
    });

    map<int, size_t> begins;
    for(size_t u = n; u --> 0; )
        begins[A[u].a] = u;

    vector<size_t> at;
    min_cost_flow_network<int, int> G(n+2, n, n+1);
    for(size_t u = 0; u < n; u++)
    {
        if(auto it = begins.upper_bound(A[u].b); it != begins.end())
        {
            auto v = it->second;
            G.add_edge(u, v, 1, -A[u].c);
            at.push_back(G.graph[u].size() - 1);
        }
        else
        {
            G.add_edge(u, n+1, 1, -A[u].c);
            at.push_back(G.graph[u].size() - 1);
        }
        if(u+1 < n)
            G.add_edge(u, u+1, k);
    }
    G.add_edge(n, 0, k);
    G.add_edge(n-1, n+1, k);

    G.min_cost_max_flow(k);
    vector<bool> result(n);
    for(size_t u = 0; u < n; u++)
    {
        int f = 0;
        if(at[u] != SIZE_MAX)
            f = G.flow_at(G.graph[u][at[u]]);
        result[A[u].i] = f;
    }

    for(auto b : result)
        cout << b << ' ';
    cout << endl;
}
