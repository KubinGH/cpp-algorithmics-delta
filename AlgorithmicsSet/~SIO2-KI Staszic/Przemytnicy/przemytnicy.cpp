#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000;
const uint64_t INF_U64 = -1llu;

struct edge_t
{
    uint32_t v; uint64_t w;
    edge_t() : v(0), w(0) {};
    edge_t(uint32_t v, uint64_t w) : v(v), w(w) {}
};
typedef pair<uint64_t, uint32_t> dt;

void dijkstra(uint32_t s, vector<edge_t> (&graph)[MAX], uint64_t (&cost)[MAX], uint32_t goal = -1u)
{
    priority_queue<dt, vector<dt>, greater<dt>> Q;
    cost[s] = 0;
    Q.emplace(0, s);
    while(not Q.empty())
    {
        uint64_t cw; uint32_t u;
        tie(cw, u) = Q.top(); Q.pop();
        if(cost[u] > cw)
            continue;
        if(goal != -1u and u == goal)
            return;
        for(edge_t e : graph[u])
        {
            uint32_t v = e.v; uint64_t w = e.w;
            if(cost[u] + w < cost[v])
            {
                cost[v] = cost[u] + w;
                Q.emplace(cost[v], v);
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint64_t base_cost[MAX];
    static vector<edge_t> graph[MAX], rev_graph[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> base_cost[i];
    uint32_t m;
    cin >> m;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; uint64_t w;
        cin >> u >> v >> w; u--; v--;
        graph[u].emplace_back(v, w);
        rev_graph[v].emplace_back(u, w);
    }
    static uint64_t src_cost[MAX], rev_cost[MAX];
    fill(src_cost, src_cost + n, INF_U64);
    fill(rev_cost, rev_cost + n, INF_U64);
    dijkstra(0, graph, src_cost);
    dijkstra(0, rev_graph, rev_cost);
    uint64_t r = base_cost[0] / 2;
    for(uint32_t i = 1; i < n; i++)
    {
        if(src_cost[i] == INF_U64 or rev_cost[i] == INF_U64)
            continue;
        r = min(r, src_cost[i] + base_cost[i]/2 + rev_cost[i]);
    }
    cout << r;
}
