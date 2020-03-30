#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX / 3;

struct edge
{
    size_t s, t;
    int cap, cost;
    size_t mate; bool rev;
    void push(int f);
    int flow() const;
};
vector<edge> edges = {{}};
void edge::push(int f) { cap -= f; edges[mate].cap += f; }
int edge::flow() const { return edges[mate].cap; }

void add_edge(vector<vector<size_t>>& graph, size_t s, size_t t, int cap, int cost = 0)
{
    size_t i = edges.size();
    edges.push_back({s, t, cap, cost, i+1, false});
    edges.push_back({t, s, 0, -cost, i, true});
    graph[s].push_back(i); graph[t].push_back(i+1);
}

pair<vector<size_t>, vector<int>> spfa(const vector<vector<size_t>>& graph, size_t source)
{
    const size_t n = graph.size();
    vector<int> dist(n, +oo);
    vector<size_t> back(n);
    vector<bool> on(n);
    queue<size_t> que;
    dist[source] = 0; que.push(source); on[source] = true;
    while(not que.empty())
    {
        auto u = que.front(); que.pop();
        on[u] = false;
        for(auto i : graph[u])
        {
            const auto& e = edges[i];
            auto v = e.t;
            if(e.cap > 0 and dist[v] > dist[u] + e.cost)
            {
                dist[v] = dist[u] + e.cost;
                back[v] = i;
                if(not on[v]) on[v] = true, que.push(v);
            }
        }
    }
    return {back, dist};
}

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

pair<vector<size_t>, vector<int>> dijkstra(const vector<vector<size_t>>& graph, const vector<int>& pi, size_t source)
{
    const size_t n = graph.size();
    vector<int> dist(n, +oo);
    vector<size_t> back(n);
    vector<bool> lock(n);
    min_priority_queue<pair<int, size_t>> Q;
    auto maybe = [&](size_t u, size_t i, int64_t d) {
        if(d < dist[u])
            Q.emplace(dist[u] = d, u), back[u] = i;
    };
    maybe(source, 0, 0);
    while(not Q.empty())
    {
        auto [_, u] = Q.top(); Q.pop();
        if(lock[u]) continue;
        lock[u] = true;
        for(auto i : graph[u])
        {
            const auto& e = edges[i];
            auto v = e.t;
            if(e.cap > 0)
                maybe(v, i, dist[u] + e.cost + pi[u] - pi[v]);
        }
    }
    return {back, dist};
}

pair<int, int> max_flow_min_cost(vector<vector<size_t>>& graph, size_t source, size_t sink)
{
    const size_t n = graph.size();
    int flow = 0, total_cost = 0;

    auto [_, pi] = spfa(graph, source);

    while(true)
    {
        auto [back, dist] = dijkstra(graph, pi, source);

        if(not back[sink])
            break;

        size_t u = sink;
        int cost = 0, f = +oo;
        while(back[u])
        {
            const auto& e = edges[back[u]];
            cost += e.cost;
            f = min(f, e.cap);
            u = e.s;
        }

        u = sink;
        while(back[u])
        {
            auto& e = edges[back[u]];
            e.push(f);
            u = e.s;
        }
        flow += f;
        total_cost += f * cost;

        if(not f)
            break;

        for(size_t v = 0; v < n; v++)
        {
            pi[v] += dist[v] + pi[v];
            pi[v] = min(pi[v], +oo);
        }
    }

    return {flow, total_cost};
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, k; int r, t;
    cin >> n >> m >> r >> t >> k;

    vector<vector<size_t>> can(n);
    for(size_t i = 0; i < k; i++)
    {
        size_t a, b;
        cin >> a >> b; a--; b--;
        can[a].push_back(b);
    }

    auto d = min(m, size_t(t / r));

    vector<vector<size_t>> G(n + m + 2);

    constexpr auto source = 0, sink = 1;
    auto v_member = [&](size_t i) { return 2 + i; };
    auto v_task = [&](size_t i) { return 2 + n + i; };

    for(size_t a = 0; a < n; a++)
    {
        for(size_t i = 1; i <= d; i++)
            add_edge(G, source, v_member(a), 1, i*r);
        for(auto b : can[a])
            add_edge(G, v_member(a), v_task(b), 1);
    }
    for(size_t b = 0; b < m; b++)
        add_edge(G, v_task(b), sink, 1);

    auto [flow, cost] = max_flow_min_cost(G, source, sink);

    cout << flow << " " << cost << endl;

    vector<uint> last(n);
    for(size_t a = 0; a < n; a++)
    {
        for(auto i : G[v_member(a)])
        {
            auto& e = edges[i];
            if(not e.rev and e.flow())
                cout << a+1 << ' ' << (e.t-2-n)+1 << ' ' << (last[a]++)*r << '\n';
        }
    }
}
