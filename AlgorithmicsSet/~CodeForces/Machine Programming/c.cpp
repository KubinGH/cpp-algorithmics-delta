#include <bits/stdc++.h>

using namespace std;

const int oo = 1e8;

struct flow_network
{
    // Skierowana krawędź sieci rezydualnej
    struct edge
    {
        size_t s, t;
        int cap, cost;
        bool rev; size_t rev_i;
    };

    size_t n, source, sink;
    // Lista sąsiedztwa
    vector<vector<edge>> graph;

    vector<int> dist; // Odległości od źródła (po kosztach)
    vector<edge*> back; // Ostatnia krawędź na najkrótszej ścieżce

    flow_network(size_t _n, size_t s, size_t t)
        : n(_n), source(s), sink(t), graph(n), dist(n), back(n) {}

    void push(edge& e, int f) { e.cap -= f; graph[e.t][e.rev_i].cap += f; }
    int flow_at(edge& e) { return e.rev ? -e.cap : graph[e.t][e.rev_i].cap; }

    // Dodaj krawędź s->t o przepustowości cap
    // Zwracane są indeksy dodanych krawędzi w listach
    pair<size_t, size_t> add_edge(size_t s, size_t t, int cap = +oo, int cost = 0)
    {
        auto i = graph[s].size(), j = graph[t].size();
        graph[s].push_back({s, t, cap, cost, false, j}); // Krawędź e
        graph[t].push_back({t, s, 0, -cost, true, i}); // Krawędź stowarzyszona e'
        return {i, j};
    }

    // SPFA (Bellman-Ford z kolejką)
    bool spfa()
    {
        fill(dist.begin(), dist.end(), +oo);
        fill(back.begin(), back.end(), nullptr);
        queue<size_t> Q;
        Q.push(source); dist[source] = 0;
        while(not Q.empty())
        {
            auto u = Q.front(); Q.pop();
            for(auto& e : graph[u])
                if(e.cap and dist[u] + e.cost < dist[e.t]) // Tylko krawędzie z sieci rezydualnej
                    Q.push(e.t), dist[e.t] = dist[u] + e.cost, back[e.t] = &e;
        }
        return dist[sink] != +oo;
    }

    // Przepływ co najwyżej danej wielkości o minimalnym koszcie
    int min_cost_flow(int flow)
    {
        int total_cost = 0;
        while(flow and spfa())
        {
            // Najtańsza ścieżka powiększająca ma koszt cost,
            // liczymy ile można przepchnąć - delta
            int delta = +oo, cost = dist[sink];
            size_t u = sink;
            while(back[u])
                delta = min(delta, back[u]->cap), u = back[u]->s;

            delta = min(delta, flow); // Nie przepychamy więcej niż można
            u = sink;
            while(back[u])
                push(*back[u], delta), u = back[u]->s;

            flow -= delta;
            total_cost += cost * delta;
        }
        return total_cost;
    }
};

struct segment { int a, b, c; size_t i; };

int main()
{
    size_t n; int k;
    cin >> n >> k;

    map<int, int> remap;
    vector<segment> A(n);
    for(size_t i = 0; i < n; i++)
    {
        auto& [a, b, c, j] = A[i];
        cin >> a >> b >> c, b += a-1;
        remap[a]; remap[b];
        j = i;
    }

    int m = 0;
    for(auto& [_, v] : remap)
        v = m++;

    for(size_t u = 0; u < n; u++)
    {
        auto& [a, b, _, __] = A[u];
        a = remap[a]; b = remap[b];
    }

    sort(A.begin(), A.end(), [](const segment& lhs, const segment& rhs) {
        return tie(lhs.a, lhs.b) < tie(rhs.a, rhs.b);
    });

    map<int, size_t> begins;
    for(size_t u = n; u --> 0; )
        begins[A[u].a] = u;

    vector<size_t> at;
    flow_network G(n+2, n, n+1);
    for(size_t u = 0; u < n; u++)
    {
        if(auto it = begins.upper_bound(A[u].b); it != begins.end())
        {
            auto v = it->second;
            at.push_back(G.add_edge(u, v, 1, -A[u].c).first);
        }
        else
            at.push_back(G.add_edge(u, n+1, 1, -A[u].c).first);
        if(u+1 < n)
            G.add_edge(u, u+1, k);
    }
    G.add_edge(n, 0, k);
    G.add_edge(n-1, n+1, k);

    G.min_cost_flow(k);
    vector<bool> result(n);
    for(size_t u = 0; u < n; u++)
    {
        int f = 0;
        if(at[u] != SIZE_MAX)
            f = G.flow_at(G.graph[u][at[u]]);
        result[A[u].i] = f;
    }

    for(auto b : result)
        cout << b << ' ';
    cout << endl;
}
