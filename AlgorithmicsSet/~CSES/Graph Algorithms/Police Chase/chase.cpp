#include <bits/stdc++.h>

using namespace std;

template<typename flow_t>
struct flow_network
{
    constexpr static flow_t oo = numeric_limits<flow_t>::max() - 0xD;

    struct edge
    {
        size_t s, t;
        flow_t cap;
        bool rev; size_t rev_i;
    };

    size_t source, sink;
    vector<vector<edge>> graph;
    vector<size_t> dist, next;

    flow_network(size_t n, size_t s, size_t t)
        : source(s), sink(t), graph(n), dist(n), next(n) {}

    void add_edge(size_t s, size_t t, flow_t cap = +oo)
    {
        graph[s].push_back({s, t, cap, false, graph[t].size()});
        graph[t].push_back({t, s, 0, true, graph[s].size() - 1});
    }

    void push(edge& e, flow_t f)
    {
        e.cap -= f;
        graph[e.t][e.rev_i].cap += f;
    }

    bool bfs()
    {
        fill(dist.begin(), dist.end(), SIZE_MAX);
        queue<size_t> que;
        auto maybe = [&](size_t u, size_t d) {
            if(dist[u] == SIZE_MAX)
                dist[u] = d, que.push(u);
        };
        maybe(source, 0);
        while(not que.empty())
        {
            auto u = que.front(); que.pop();
            for(auto e : graph[u])
                if(e.cap)
                    maybe(e.t, dist[u] + 1);
        }
        return dist[sink] != SIZE_MAX;
    }

    flow_t augment(size_t u, flow_t lim = +oo)
    {
        if(u == sink)
            return lim;
        if(not lim)
            return 0;

        flow_t delta = 0;
        if(dist[u] < dist[sink])
          for(size_t& i = next[u]; i < graph[u].size() and delta < lim; i++)
        {
            auto& e = graph[u][i];
            if(e.cap and dist[e.t] == dist[u] + 1)
            {
                auto f = augment(e.t, min(e.cap, lim - delta));
                delta += f; push(e, f);
                if(delta == lim)
                    break;
            }
        }
        if(not delta)
            dist[u] = SIZE_MAX;
        return delta;
    }

    flow_t max_flow()
    {
        flow_t flow = 0;
        while(bfs() and flow < +oo)
            fill(next.begin(), next.end(), 0), flow += augment(source);
        return min(flow, +oo);
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    flow_network<int> F(n + 1, 1, n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        F.add_edge(u, v, 1);
        F.add_edge(v, u, 1);
    }

    cout << F.max_flow() << '\n';

    vector<size_t> cut;
    vector<bool> in_cut(n + 1);
    function<void(size_t)> dfs = [&](size_t u) {
        if(in_cut[u])
            return;
        in_cut[u] = true;
        cut.push_back(u);
        for(auto e : F.graph[u])
            if(e.cap)
                dfs(e.t);
    };
    dfs(1);

    for(auto u : cut)
        for(auto e : F.graph[u])
            if(not e.rev and not in_cut[e.t])
                cout << e.s << ' ' << e.t << '\n';
}
