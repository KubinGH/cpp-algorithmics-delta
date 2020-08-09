#include <bits/stdc++.h>

using namespace std;

const size_t nul = SIZE_MAX;
const uint64_t oo = UINT64_MAX / 3;

struct flow_network
{
    struct edge
    {
        size_t s, t;
        uint cap;
        size_t rev_i;
    };

    uint64_t flow = 0;
    vector<vector<edge>> graph;
    vector<size_t> dist, next_edge;
    size_t source, sink;

    flow_network(size_t n, size_t s, size_t t)
        : graph(n), dist(n), next_edge(n), source(s), sink(t) {}

    void push(edge& e, uint f)
    {
        e.cap -= f;
        graph[e.t][e.rev_i].cap += f;
    }

    void add_edge(size_t s, size_t t, uint cap)
    {
        graph[s].push_back({s, t, cap, graph[t].size()});
        graph[t].push_back({t, s, 0, graph[s].size() - 1});
    }

    bool next_iteration()
    {
        fill(dist.begin(), dist.end(), nul);
        fill(next_edge.begin(), next_edge.end(), 0);

        queue<size_t> Q;
        dist[source] = 0; Q.push(source);
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for(auto e : graph[u])
                if(e.cap and dist[e.t] == nul)
                    dist[e.t] = dist[e.s] + 1, Q.push(e.t);
        }
        return dist[sink] != nul;
    }

    uint64_t augment(size_t u, uint64_t lim = +oo)
    {
        if(u == sink)
            return lim;
        if(not lim or dist[u] > dist[sink])
            return 0;

        uint64_t delta = 0;
        for(size_t& i = next_edge[u]; i < graph[u].size(); i++)
        {
            auto& e = graph[u][i];
            size_t v = e.t;
            if(dist[v] == dist[u] + 1)
            {
                auto c = augment(v, min(lim - delta, (uint64_t)e.cap));
                push(e, c);
                delta += c;
            }
            if(delta == lim)
                break;
        }

        return delta;
    }

    uint64_t max_flow()
    {
        while(next_iteration())
            flow += augment(source);
        return flow;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    flow_network F(n, 0, n - 1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; uint c;
        cin >> u >> v >> c; u--; v--;
        F.add_edge(u, v, c);
        F.add_edge(v, u, c);
    }

    cout << F.max_flow() << endl;
}
