#include <bits/stdc++.h>

using namespace std;

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

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    size_t h, w, x1, y1, x2, y2;
    cin >> h >> w >> x1 >> y1 >> x2 >> y2;
    x1--; y1--; x2--; y2--;

    const size_t n = w*h;

    flow::graph G(2*n);

    vector<vector<uint32_t>> A(h, vector<uint32_t>(w));

    auto I = [&](size_t x, size_t y) {
        return y * w + x;
    };
    for(size_t y = 0; y < h; y++)
    {
        for(size_t x = 0; x < w; x++)
        {
            cin >> A[y][x];
            G[I(x, y)].push_back({n+I(x, y), A[y][x]});
            if(x+1 < w) G[n+I(x, y)].push_back({I(x+1, y), UINT32_MAX});
            if(x-1 < w) G[n+I(x, y)].push_back({I(x-1, y), UINT32_MAX});
            if(y+1 < h) G[n+I(x, y)].push_back({I(x, y+1), UINT32_MAX});
            if(y-1 < h) G[n+I(x, y)].push_back({I(x, y-1), UINT32_MAX});
        }
    }

    cout << dinic::find_max_flow(G, I(x1, y1), n+I(x2, y2)).first;
}