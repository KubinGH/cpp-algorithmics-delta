#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef unsigned uint;

struct edge
{
    size_t v; uint c;
    edge(size_t _v, uint _c) : v(_v), c(_c) {}
};
struct bnd_edge
{
    size_t u, v; uint c; size_t rev_i;
    bnd_edge(size_t _u, size_t _v, uint _c, size_t _rev_i)
        : u(_u), v(_v), c(_c), rev_i(_rev_i) {}
};

typedef vector<vector<edge> > graph;
typedef vector<vector<bnd_edge> > bnd_graph;


uint dfs_extend(uint u, uint lim, bnd_graph& F, const vector<uint>& dist, vector<uint>& next_edge, size_t source, size_t sink)
{
    if(u == sink)
        return lim;
    uint r = 0;
    for(uint& i = next_edge[u]; i < F[u].size() and lim; i++)
    {
        bnd_edge& e = F[u][i];
        if(dist[e.v] == dist[u] + 1)
        {
            uint x = dfs_extend(e.v, min(lim, e.c), F, dist, next_edge, source, sink);
            if(x)
            {
                e.c -= x;
                F[e.v][e.rev_i].c += x;
            }
            lim -= x;
            r += x;
            if(not lim)
                break;
        }
    }
    return r;
}

namespace dinic
{
    pair<uint, graph> find_max_flow(const graph& G, size_t source, size_t sink)
    {
        const size_t n = G.size();
        bnd_graph F(n);
        for(uint u = 0; u < n; u++)
            for(size_t i = 0; i < G[u].size(); i++)
        {
            edge e = G[u][i];
            F[u].push_back(bnd_edge(u, e.v, e.c, F[e.v].size()));
            F[e.v].push_back(bnd_edge(e.v, u, 0, F[u].size() - 1));
        }
        uint max_flow = 0;

        bool done = false;

        vector<uint> dist(n), next_edge(n);
        do {
            done = true;

            queue<uint> tovis;
            fill(dist.begin(), dist.end(), -1u);
            fill(next_edge.begin(), next_edge.end(), 0);
            dist[source] = 0; tovis.push(source);
            while(not tovis.empty())
            {
                uint u = tovis.front(); tovis.pop();
                for(uint i = 0; i < F[u].size(); i++)
                {
                    bnd_edge e = F[u][i];
                    if(e.c and dist[e.v] == -1u)
                    {
                        dist[e.v] = dist[u] + 1;
                        tovis.push(e.v);
                    }
                }
            }

            uint x = dfs_extend(source, 1<<30, F, dist, next_edge, source, sink);
            if(x)
            {
                max_flow += x;
                done = false;
            }
        } while(not done);


        graph R(n);
        for(uint u = 0; u < n; u++)
            for(size_t i = 0; i < F[u].size(); i++)
        {
            bnd_edge e = F[u][i];
            R[u].push_back(edge(e.v, F[e.v][e.rev_i].c));
        }

        return make_pair(max_flow, R);
    }
}

int main()
{
    unsigned n, m;
    scanf("%u %u", &n, &m);

    graph G(2+n);

    for(size_t i = 0; i < n; i++)
    {
        uint x, y;
        scanf("%u %u", &x, &y);
        G[0].push_back(edge(2+i, x));
        G[2+i].push_back(edge(1, y));
    }
    for(size_t i = 0; i < m; i++)
    {
        unsigned a, b; uint z;
        scanf("%u %u %u", &a, &b, &z); a--; b--;
        G[2+a].push_back(edge(2+b, z));
        G[2+b].push_back(edge(2+a, z));
    }

    printf("%d", dinic::find_max_flow(G, 0, 1).first);
}
