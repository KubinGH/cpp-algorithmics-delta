#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20;

template<size_t N>
using graph_t = array<vector<uint32_t>, N>;

bitset<MAX> vis;
void marker_dfs(uint32_t u, graph_t<MAX>& graph, vector<uint32_t>& out)
{
    for(uint32_t v : graph[u])
        if(not vis[v])
            vis[v] = true, marker_dfs(v, graph, out);
    out.push_back(u);
}

vector<vector<uint32_t>>
kosaraju(uint32_t n, graph_t<MAX>& graph, graph_t<MAX>& rev_graph)
{
    vector<uint32_t> order; order.reserve(n);
    vis.reset();
    for(uint32_t u = 0; u < n; u++)
        if(not vis[u])
            vis[u] = true, marker_dfs(u, graph, order);
    reverse(order.begin(), order.end());
    vis.reset();
    vector<vector<uint32_t>> result;
    for(uint32_t u : order)
    {
        if(not vis[u])
        {
            result.emplace_back();
            vis[u] = true;
            marker_dfs(u, rev_graph, result.back());
        }
    }
    return result;
}

int main()
{
    uint32_t n, m;
    cin >> n >> m;
    static graph_t<MAX> graph, rev_graph;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        rev_graph[v].push_back(u);
    }
    vector<vector<uint32_t>> strong_components = kosaraju(n, graph, rev_graph);
    for(auto comp : strong_components)
    {
        cout << "( ";
        for(uint32_t u : comp)
            cout << u+1 << " ";
        cout << ")\n";
    }
}

/*
7 10

1 2
2 1
2 5
5 4
1 4
3 2
3 7
7 6
6 3
6 5
*/