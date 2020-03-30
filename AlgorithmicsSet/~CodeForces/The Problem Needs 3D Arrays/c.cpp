#include <bits/stdc++.h>

using namespace std;

const double oo = 1e9;
const double eps = 1e-8;

struct flow_network
{
    using flow_t = double;

    // Skierowana krawędź w sieci rezydualnej
    struct edge
    {
        size_t s, t; flow_t cap;
        size_t mate; bool rev;
        void push(vector<edge>& E, flow_t f) { cap -= f; E[mate].cap += f; }
        flow_t flow(const vector<edge>& E) const { return E[mate].cap; }
    };

    size_t n;
    vector<edge> edges = {{}}; // Nieużywana krawędź zerowa
    vector<vector<size_t>> graph; // Lista sąsiedztwa (indeks krawędzi)

    // Rzeczy potrzebne w BFS - są tutaj, żeby było wydajniej
    vector<bool> vis;
    vector<size_t> back;

    flow_network(size_t _n) : n(_n), graph(n), vis(n), back(n) {}

    size_t add_edge(size_t u, size_t v, flow_t c)
    {
        const auto i = edges.size();
        edges.push_back({u, v, c, i+1, false});
        edges.push_back({v, u, 0, i, true});
        graph[u].push_back(i);
        graph[v].push_back(i+1);
        return i;
    }

    // Szukanie ścieżek powiększających BFSem
    void bfs(size_t source)
    {
        fill(vis.begin(), vis.end(), false);
        fill(back.begin(), back.end(), 0);

        queue<size_t> Q;
        Q.push(source); vis[source] = true;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for(auto i : graph[u])
            {
                const auto& e = edges[i];
                // Chodzimy tylko krawędziami o dodatniej przepustowości rezydualnej
                if(e.cap > eps and not vis[e.t])
                    Q.push(e.t), vis[e.t] = true, back[e.t] = i;
            }
        }
    }

    // Edmonds-Karp
    flow_t max_flow(size_t source, size_t sink)
    {
        flow_t flow = 0;

        while(true)
        {
            bfs(source);
            if(not vis[sink])
                break;

            // Liczymy, ile możemy przepchnąć
            flow_t delta = +oo;
            auto u = sink;
            while(back[u])
            {
                auto& e = edges[back[u]];
                delta = min(delta, e.cap);
                u = e.s;
            }
            // Przepychamy
            u = sink;
            while(back[u])
            {
                auto& e = edges[back[u]];
                e.push(edges, delta);
                u = e.s;
            }
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

        flow_network G(2 + inv.size() + n);
        vector<size_t> unit_e, inf_e, a_e;
        for(size_t i = 0; i < inv.size(); i++)
        {
            auto [u, v] = inv[i];
            unit_e.push_back(G.add_edge(0, 2+i, 1));
            inf_e.push_back(G.add_edge(2+i, 2+inv.size()+u, +oo));
            inf_e.push_back(G.add_edge(2+i, 2+inv.size()+v, +oo));
        }
        for(size_t u = 0; u < n; u++)
            a_e.push_back(G.add_edge(2+inv.size()+u, 1, 42));

        double lo = 0, hi = 64;
        while(hi - lo > eps)
        {
            double a = (lo + hi) / 2;

            for(auto i : unit_e)
                G.edges[i].cap = 1, G.edges[i+1].cap = 0;
            for(auto i : inf_e)
                G.edges[i].cap = +oo, G.edges[i+1].cap = 0;
            for(auto i : a_e)
                G.edges[i].cap = a, G.edges[i+1].cap = 0;

            auto f = G.max_flow(0, 1);
            if((double)inv.size() - f <= 0)
                hi = a;
            else
                lo = a;
        }

        cout << "Case #" << cs << ": " << lo << '\n';
    }
}
