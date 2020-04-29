#pragma GCC optimize("Ofast")
#pragma GCC optimization("O3")
#pragma GCC optimization("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

/* */

#define getchar() (S == T && (T = (S = BB) + fread(BB, 1, 1 << 15, stdin), S == T) ? EOF : *S++)
char BB[1 << 20], *S = BB, *T = BB;
template<typename dt>
inline void read(dt& x)
{
    x = 0;
    int w = 1;
    char ch = 0;
    while(!isdigit(ch))
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while(isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    x *= w;
}

/* */

struct flow_network
{
    constexpr static auto oo = numeric_limits<uint>::max() - 0xF;

    struct edge
    {
        size_t t;
        uint cap;
        size_t rev_i;
    };

    size_t n, source, sink;
    vector<edge> graph[2048];

    uint dist[2048];
    size_t curr_edge[2048];

    uint64_t bound = 1;
    uint max_cap = 0;

    flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t) {}

    void add_edge(size_t s, size_t t, uint cap = +oo)
    {
        graph[s].push_back({t, cap, graph[t].size()});
        graph[t].push_back({s, 0, graph[s].size() - 1});
        max_cap = max(max_cap, cap);
    }

    bool bfs()
    {
        queue<size_t> Q;
        fill(dist, dist + n, 0);
        Q.push(sink); dist[sink] = 1;
        while(not Q.empty() and not dist[source])
        {
            auto u = Q.front(); Q.pop();
            for(auto e : graph[u])
                if(not dist[e.t] and graph[e.t][e.rev_i].cap >= bound)
                    Q.push(e.t), dist[e.t] = dist[u] + 1;
        }
        return dist[source];
    }

    uint augment_dfs(size_t u, uint lim)
    {
        if(not lim or u == sink)
            return lim;
        uint delta = 0;
        for(; curr_edge[u] < graph[u].size(); curr_edge[u]++)
        {
            auto& e = graph[u][curr_edge[u]];
            if(dist[e.t] == dist[u] - 1 and e.cap)
            {
                auto x = augment_dfs(e.t, min(lim - delta, e.cap));
                e.cap -= x;
                graph[e.t][e.rev_i].cap += x;
                delta += x;
                if(delta == lim)
                    return delta;
            }
        }
        if(not delta)
            dist[u] = 0;
        return delta;
    }

    uint max_flow()
    {
        uint flow = 0;
        if(bound <= max_cap)
        {
            while(bound <= max_cap) bound *= 22;
            bound /= 22;
        }

        for(; bound; bound /= 22)
        {
            while(bfs())
            {
                fill(curr_edge, curr_edge + n, 0);
                flow += augment_dfs(source, +oo);
            }
        }
        return flow;
    }
};

int main()
{
    size_t n, m, s, t;
    read(n); read(m); read(s); read(t); s--; t--;

    static flow_network G(n, t, s);

    vector<tuple<size_t, size_t, uint>> E; E.reserve(m);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; uint c;
        read(u); read(v); read(c); u--; v--;
        E.emplace_back(u, v, c);
    }

    shuffle(E.begin(), E.end(), mt19937{});
    for(auto [u, v, c] : E)
        G.add_edge(v, u, c);

    cout << G.max_flow() << endl;
}
