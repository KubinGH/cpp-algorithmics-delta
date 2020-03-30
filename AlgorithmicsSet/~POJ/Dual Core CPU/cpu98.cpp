#include <cstring>
#include <vector>
#include <cstdio>

using namespace std;

typedef unsigned uint;
const uint oo = 1e9;
const size_t N = 1 << 15, M = 1 << 20;

struct flow_network
{
    typedef uint flow_t;
    struct edge
    {
        size_t s, t;
        flow_t cap; bool rev;
        edge() {}
        edge(size_t _s, size_t _t, flow_t _c, bool _r)
            : s(_s), t(_t), cap(_c), rev(_r) {}
    };

    size_t n, source, sink;
    vector<size_t> graph[N];
    edge edges[M]; size_t ect;

    int dist[N];
    size_t curr_edge[N], Q[N];

    flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t), ect(0) {}

    inline void push(size_t i, flow_t f) { edges[i].cap -= f; edges[i^1].cap += f; }
    flow_t flow_at(size_t i) { return edges[i^1].cap; }

    inline size_t add_edge(size_t s, size_t t, flow_t cap)
    {
        size_t i = ect;
        edges[ect++] = edge(s, t, cap, false);
        edges[ect++] = edge(t, s, 0, true);
        graph[s].push_back(i); graph[t].push_back(i+1);
        return i;
    }

    bool bfs()
    {
        memset(dist, 0xff, sizeof (dist));
        size_t qi = 0;
        Q[qi++] = source; dist[source] = 0;
        for(size_t i = 0; i < qi; i++)
        {
            size_t u = Q[i];
            for(size_t j = 0; j < graph[u].size(); j++)
            {
                const edge& e = edges[graph[u][j]];
                if(e.cap and dist[e.t] == -1)
                    Q[qi++] = e.t, dist[e.t] = dist[u] + 1;
            }
        }
        return dist[sink] != -1;
    }

    flow_t augment_dfs(size_t u, flow_t lim)
    {
        if(u == sink)
            return lim;
        flow_t delta = 0;
        if(dist[u] < dist[sink])
            for(size_t& j = curr_edge[u]; j < graph[u].size(); j++)
        {
            edge& e = edges[graph[u][j]];
            if(e.cap and dist[e.t] == dist[u] + 1)
            {
                flow_t x = augment_dfs(e.t, min(lim - delta, e.cap));
                push(graph[u][j], x); delta += x;
            }
            if(delta == lim)
                break;
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
            // Przepływ blokujący
            memset(curr_edge, 0, sizeof (curr_edge));
            flow += augment_dfs(source, +oo);
        }
        return flow;
    }
};

int main()
{
    unsigned n, m;
    scanf("%u %u", &n, &m);

    static flow_network G(2 + n, 0, 1);
    for(size_t i = 0; i < n; i++)
    {
        uint x, y;
        scanf("%u %u", &x, &y);
        G.add_edge(0, 2+i, x);
        G.add_edge(2+i, 1, y);
    }
    for(size_t i = 0; i < m; i++)
    {
        unsigned a, b; uint z;
        scanf("%u %u %u", &a, &b, &z); a--; b--;
        G.add_edge(2+a, 2+b, z);
        G.add_edge(2+b, 2+a, z);
    }

    printf("%d", G.max_flow());
}
