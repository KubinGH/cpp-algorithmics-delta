#include <bits/stdc++.h>

using namespace std;

struct edge
{
    size_t v, i;
};

vector<vector<edge>> graph;
vector<bool> vis;

void visit(size_t u, vector<size_t>& out, bool init, size_t initial, bool& cycle)
{
    if(not init and u == initial)
        cycle = true;
    for(auto e : graph[u])
    {
        if(not vis[e.i])
        {
            vis[e.i] = true;
            out.push_back(e.i);
            visit(e.v, out, false, initial, cycle);
        }
    }
}

void dfs(size_t u)
{
    for(auto e : graph[u])
    {
        if(not vis[e.i])
            vis[e.i] = true, dfs(e.v);
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<pair<size_t, size_t>> edges;
    graph.resize(n);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        edges.emplace_back(u, v);
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
    }

    bool deg2 = true;
    for(size_t i = 0; i < n; i++)
        if(graph[i].size() > 2)
            deg2 = false;

    vis.resize(m);

    if(n <= 20)
    {
        int result = 0;
        for(size_t s = 0; s < (1u << m); s++) if(__builtin_popcount(s) == 4)
        {
            graph = vector<vector<edge>>{};
            graph.resize(n);
            fill(vis.begin(), vis.end(), false);

            size_t a;
            for(size_t i = 0; i < m; i++)
                if(s >> i & 1)
            {
                a = edges[i].first;
                graph[edges[i].first].push_back({edges[i].second, i});
                graph[edges[i].second].push_back({edges[i].first, i});
            }

            dfs(a);

            if(count(vis.begin(), vis.end(), true) == 4)
                result++;
        }
        cout << result;
    }
    else if(deg2)
    {
        int result = 0;
        for(size_t u = 0; u < n; u++)
        {
            vector<size_t> hist;
            bool cycle = false;
            visit(u, hist, true, u, cycle);
            if(hist.size() < 4)
                continue;
            else if(cycle)
            {
                if(hist.size() == 4)
                    result++;
                else
                    result += hist.size();
            }
            else
                result += hist.size() - 3;
        }
        cout << result;
    }
    else
    {
        abort();
    }
}
