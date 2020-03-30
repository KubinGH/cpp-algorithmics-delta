#include <bits/stdc++.h>

using namespace std;

const int64_t oo = 1e18, mul = 1e9;

struct flow_network
{
    using flow_t = int64_t;

    struct edge
    {
        size_t s, t; flow_t cap;
        size_t mate; bool rev;
        void push(vector<edge>& E, flow_t f) { cap -= f; E[mate].cap += f; }
        flow_t flow(const vector<edge>& E) const { return E[mate].cap; }
    };
    size_t n, source, sink;
    vector<edge> edges = {{}};
    vector<vector<size_t>> graph;

    vector<bool> vis;
    vector<int> dist;

    vector<size_t> curr;

    flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t), graph(n), vis(n), dist(n), curr(n) {}

    size_t add_edge(size_t u, size_t v, flow_t c)
    {
        const auto i = edges.size();
        edges.push_back({u, v, c, i+1, false});
        edges.push_back({v, u, 0, i, true});
        graph[u].push_back(i);
        graph[v].push_back(i+1);
        return i;
    }

    void bfs()
    {
        fill(vis.begin(), vis.end(), false);
        fill(dist.begin(), dist.end(), -1);

        queue<size_t> Q;
        Q.push(source); vis[source] = true;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for(auto i : graph[u])
            {
                const auto& e = edges[i];
                if(e.cap and not vis[e.t])
                    Q.push(e.t), vis[e.t] = true, dist[e.t] = dist[e.s] + 1;
            }
        }
    }

    flow_t augment_dfs(size_t u, flow_t lim)
    {
        if(u == sink)
            return lim;
        flow_t delta = 0;
        if(dist[u] < dist[sink])
          for(size_t& j = curr[u]; j < graph[u].size(); j++)
        {
            auto& e = edges[graph[u][j]]; const auto v = e.t;
            if(e.cap and dist[v] == dist[u] + 1)
            {
                auto x = augment_dfs(v, min(lim - delta, e.cap));
                e.push(edges, x); delta += x;
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

        while(true)
        {
            bfs();
            if(not vis[sink]) break;

            fill(curr.begin(), curr.end(), 0);
            auto delta = augment_dfs(source, +oo);
            flow += delta;
        }

        return flow;
    }
};


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t T;
    cin >> T;

    cout << fixed << setprecision(7);
    for(size_t cs = 1; cs <= T; cs++)
    {
        size_t n;
        cin >> n;

        vector<int> P(n);
        for(size_t i = 0; i < n; i++)
            cin >> P[i];

        vector<pair<size_t, size_t>> inv;
        for(size_t i = 0; i < n; i++)
            for(size_t j = i+1; j < n; j++)
                if(P[i] > P[j])
                    inv.emplace_back(i, j);

        flow_network G(2 + inv.size() + n, 0, 1);
        vector<size_t> unit_e, inf_e, a_e;
        for(size_t i = 0; i < inv.size(); i++)
        {
            auto [u, v] = inv[i];
            unit_e.push_back(G.add_edge(0, 2+i, 42));
            inf_e.push_back(G.add_edge(2+i, 2+inv.size()+u, 42));
            inf_e.push_back(G.add_edge(2+i, 2+inv.size()+v, 42));
        }
        for(size_t u = 0; u < n; u++)
            a_e.push_back(G.add_edge(2+inv.size()+u, 1, 42));

        double lo = 0, hi = 64;
        while(hi - lo > 1e-8)
        {
            double a = (lo + hi) / 2;

            for(auto i : unit_e)
                G.edges[i].cap = 1*mul, G.edges[i+1].cap = 0;
            for(auto i : inf_e)
                G.edges[i].cap = +oo, G.edges[i+1].cap = 0;
            for(auto i : a_e)
                G.edges[i].cap = a*mul, G.edges[i+1].cap = 0;

            auto f = G.max_flow();
            if(inv.size()*mul - f <= 0)
                hi = a;
            else
                lo = a;
        }

        cout << "Case #" << cs << ": " << lo << '\n';
    }
}
