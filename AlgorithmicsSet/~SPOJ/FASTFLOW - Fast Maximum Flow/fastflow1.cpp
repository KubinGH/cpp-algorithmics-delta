#include <bits/stdc++.h>

using namespace std;

const uint64_t oo = UINT64_MAX / 3;

struct flow_network
{
    using flow_t = uint64_t;
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

    flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t), graph(n), dist(n), curr_edge(n) {}

    void push(edge& e, flow_t f) { e.cap -= f; graph[e.t][e.rev_i].cap += f; }
    flow_t flow_at(edge& e) { return graph[e.t][e.rev_i].cap; }

    void add_edge(size_t s, size_t t, flow_t cap)
    {
        graph[s].push_back({s, t, cap, false, graph[t].size()});
        graph[t].push_back({t, s, 0, true, graph[s].size() - 1});
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
                if(e.cap and dist[e.t] == -1)
                    Q.push(e.t), dist[e.t] = dist[u] + 1;
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
            auto& e = graph[u][j]; const auto v = e.t;
            if(e.cap and dist[v] == dist[u] + 1)
            {
                auto x = augment_dfs(v, min(lim - delta, e.cap));
                push(e, x); delta += x;
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
            fill(curr_edge.begin(), curr_edge.end(), 0);
            flow += augment_dfs(source, +oo);
        }
        return flow;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    flow_network G(n, 0, n - 1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int64_t c;
        cin >> u >> v >> c; u--; v--;
        G.add_edge(u, v, c);
        G.add_edge(v, u, c);
    }

    cout << G.max_flow();
}
