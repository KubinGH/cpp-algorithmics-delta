#include <bits/stdc++.h>

using namespace std;

const uint64_t oo = UINT64_MAX / 3;

struct flow_network
{
    using flow_t = uint64_t;
    // Skierowana krawędź sieci rezydualnej
    struct edge
    {
        size_t s, t;
        flow_t cap; bool rev;
        size_t mate;
    };

    size_t n, source, sink;
    // Lista sąsiedztwa (po indeksach krawędzi)
    vector<vector<size_t>> graph;
    // Lista wszystkich krawędzi
    // Nieużywane krawędzie 0 i 1 - dzięki temu 0 jest puste i towarzysz i to zawsze i^1
    vector<edge> edges = {{}, {}};

    vector<int> dist; // Odległości od źródła (BFS)
    vector<size_t> curr_edge; // DFS

    flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t), graph(n), dist(n), curr_edge(n) {}

    void push(edge& e, flow_t f) { e.cap -= f; edges[e.mate].cap += f; }
    flow_t flow_at(edge& e) { return edges[e.mate].cap; }

    // Dodaj krawędź s->t o przepustowości cap
    size_t add_edge(size_t s, size_t t, flow_t cap)
    {
        auto i = edges.size();
        edges.push_back({s, t, cap, false, i+1}); // Krawędź e
        edges.push_back({t, s, 0, true, i}); // Krawędź stowarzyszona e'
        graph[s].push_back(i); graph[t].push_back(i+1);
        return i;
    }

    // BFS liczy graf poziomowy, czyli odległości
    bool bfs()
    {
        fill(dist.begin(), dist.end(), -1);
        queue<size_t> Q;
        Q.push(source); dist[source] = 0;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for(auto i : graph[u])
            {
                const auto& e = edges[i]; const auto v = e.t;
                if(e.cap and dist[v] == -1) // Tylko krawędzie w sieci rezydualnej
                    Q.push(v), dist[v] = dist[u] + 1;
            }
        }
        return dist[sink] != -1;
    }

    // DFS szuka ścieżek powiększających w grafie poziomowym
    // Zwraca przepchnięty przepływ
    flow_t augment_dfs(size_t u, flow_t lim)
    {
        if(u == sink)
            return lim;
        flow_t delta = 0;
        // Pomijamy krawędzie, przez które nie da się nic przepchnąć
        // oraz wierzchołki "za" źródłem
        if(dist[u] < dist[sink])
          for(size_t& j = curr_edge[u]; j < graph[u].size(); j++)
        {
            auto& e = edges[graph[u][j]]; const auto v = e.t;
            // Krawędzie w sieci rezydualnej i grafie poziomowym
            if(e.cap and dist[v] == dist[u] + 1)
            {
                auto x = augment_dfs(v, min(lim - delta, e.cap));
                // Modyfikujemy przepływ
                push(e, x); delta += x;
            }
            // Jeżeli to nam skończył się lim, to przerywamy (i nie wyrzucamy krawędzi)
            if(delta == lim)
                break;
        }
        // Wyrzucamy wierzchołki z grafu poziomowego
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

    flow_network G(2 + n, 0, 1);
    for(size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        G.add_edge(0, 2+i, x);
        G.add_edge(2+i, 1, y);
    }
    for(size_t i = 0; i < m; i++)
    {
        size_t a, b; int z;
        cin >> a >> b >> z; a--; b--;
        G.add_edge(2+a, 2+b, z);
        G.add_edge(2+b, 2+a, z);
    }

    cout << G.max_flow();
}
