#include <bits/stdc++.h>

using namespace std;

struct edge_t { uint32_t v, i; bool d; };
typedef vector<vector<edge_t>> lgraph_t;
typedef vector<vector<uint32_t>> graph_t;

void dfs_direct(uint32_t u, const lgraph_t& graph, vector<bool>& vis, 
                vector<bool>& evis, vector<bool>& dir, graph_t& dir_graph)
{
    vis[u] = true;
    for(auto e : graph[u])
    {
        if(not evis[e.i])
        {
            evis[e.i] = true;
            dir[e.i] = e.d;
            dir_graph[u].push_back(e.v);
        }
        if(not vis[e.v])
            dfs_direct(e.v, graph, vis, evis, dir, dir_graph);
    }
}

void marker_dfs(uint32_t u, const graph_t& graph, vector<bool>& vis, 
                vector<uint32_t>& marker)
{
    vis[u] = true;
    for(uint32_t v : graph[u])
        if(not vis[v])
            marker_dfs(v, graph, vis, marker);
    marker.push_back(u);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    lgraph_t graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back({v, i, 0});
        graph[v].push_back({u, i, 1});
    }
    vector<bool> vis(n), evis(m), dir(m);
    graph_t dir_graph(n);
    for(uint32_t u = 0; u < n; u++)
        if(not vis[u])
            dfs_direct(u, graph, vis, evis, dir, dir_graph);

    graph_t dir_graph_rev(n);
    for(uint32_t u = 0; u < n; u++)
        for(uint32_t v : dir_graph[u])
            dir_graph_rev[v].push_back(u);
    
    fill(vis.begin(), vis.end(), false);
    vector<uint32_t> order; order.reserve(n);
    for(uint32_t u = 0; u < n; u++)
        if(not vis[u])
            marker_dfs(u, dir_graph, vis, order);
    
    reverse(order.begin(), order.end());
    fill(vis.begin(), vis.end(), false);
    uint32_t scc_count = 0;
    for(uint32_t u : order)
    {
        if(not vis[u])
        {
            vector<uint32_t> c;
            marker_dfs(u, dir_graph_rev, vis, c);
            scc_count++;
        }
    }
    cout << scc_count << "\n";
    for(uint32_t i = 0; i < m; i++)
        cout << (dir[i] ? '<' : '>');
    cout << endl;
}