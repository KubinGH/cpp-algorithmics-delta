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

vector<size_t> spfa(const vector<vector<size_t>>& graph, size_t source)
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
    return back;
}

int max_budget_flow(vector<vector<size_t>>& graph, size_t source, size_t sink, int budget)
{
    int flow = 0;

    while(true)
    {
        auto back = spfa(graph, source);
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

        f = min(f, cost ? budget / cost : +oo);
        u = sink;
        while(back[u])
        {
            auto& e = edges[back[u]];
            e.push(f);
            u = e.s;
        }
        flow += f;
        budget -= f * cost;

        if(not f)
            break;
    }

    return flow;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; int k;
    cin >> n >> k;

    vector<vector<size_t>> graph(n);
    for(size_t u = 0; u < n; u++)
      for(size_t v = 0; v < n; v++)
    {
        int c;
        cin >> c;
        if(c)
        {
            add_edge(graph, u, v, c);
            add_edge(graph, u, v, +oo, 1);
        }
    }

    cout << max_budget_flow(graph, 0, n - 1, k);
}
