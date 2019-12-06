#include <bits/stdc++.h>

// -*- ktl/graph/flow/flow-graph.hpp -*-

#include <vector>
#include <cstdint>

using std::uint32_t;
using std::size_t;
using std::vector;

namespace flow
{
    using capacity_t = uint32_t;

    struct edge
    {
        size_t v; capacity_t c;
        edge(size_t _v, capacity_t _c) : v(_v), c(_c) {}
    };
    struct bnd_edge
    {
        size_t u, v; capacity_t c; size_t rev_i;
        bnd_edge(size_t _u, size_t _v, capacity_t _c, size_t _rev_i)
            : u(_u), v(_v), c(_c), rev_i(_rev_i) {}
    };

    using graph = vector<vector<edge>>;
    using bnd_graph = vector<vector<bnd_edge>>;
}

// -$- ktl/graph/flow/flow-graph.hpp -$-

// -*- ktl/graph/flow/dinic.cpp -*-

#include <functional>
#include <utility>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using std::fill; using std::min;
using std::vector; using std::pair; using std::queue;
using std::size_t;
using std::function;
using std::numeric_limits;

namespace dinic
{
    using namespace flow;
    pair<capacity_t, graph> find_max_flow(const graph& G, size_t source, size_t sink)
    {
        const size_t n = G.size();
        bnd_graph F(n);
        for(size_t u = 0; u < n; u++)
            for(auto e : G[u])
        {
            F[u].emplace_back(u, e.v, e.c, F[e.v].size());
            F[e.v].emplace_back(e.v, u, 0, F[u].size() - 1);
        }
        capacity_t max_flow = 0;

        bool done = false;

        vector<size_t> dist(n), next_edge(n);
        do {
            done = true;

            queue<size_t> tovis;
            fill(dist.begin(), dist.end(), SIZE_MAX);
            fill(next_edge.begin(), next_edge.end(), 0);
            dist[source] = 0; tovis.push(source);
            while(not tovis.empty())
            {
                size_t u = tovis.front(); tovis.pop();
                for(size_t i = 0; i < F[u].size(); i++)
                {
                    auto e = F[u][i];
                    if(e.c and dist[e.v] == SIZE_MAX)
                    {
                        dist[e.v] = dist[u] + 1;
                        tovis.push(e.v);
                    }
                }
            }

            function<capacity_t(size_t, capacity_t)> dfs_extend = [&](size_t u, capacity_t lim) {
                if(u == sink)
                    return lim;
                capacity_t r = 0;
                for(size_t& i = next_edge[u]; i < F[u].size() and lim; i++)
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
            auto x = dfs_extend(source, numeric_limits<capacity_t>::max());
            max_flow += x;
            if(x)
                done = false;
        } while(not done);


        graph R(n);
        for(size_t u = 0; u < n; u++)
            for(auto e : F[u])
                R[u].emplace_back(e.v, F[e.v][e.rev_i].c);

        return {max_flow, R};
    }
}

// -$- ktl/graph/flow/dinic.cpp -$-


using namespace std;

int main()
{
    ifstream cin("rps2.in");
    ofstream cout("rps2.out");

    uint32_t a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;

    flow::graph G(8);

    const uint32_t W = 1 << 27;
    vector<tuple<size_t, size_t, uint32_t>> edges = {
        {0, 1, a}, {0, 2, b}, {0, 3, c},
        {1, 4, W}, {1, 6, W},
        {2, 4, W}, {2, 5, W},
        {3, 5, W}, {3, 6, W},
        {4, 7, d}, {5, 7, e}, {6, 7, f}
    };

    for(auto [u, v, w] : edges)
        G[u].push_back({v, w});

    auto [result, G1] = dinic::find_max_flow(G, 0, 7);

    cout << (a+b+c) - result;
}
