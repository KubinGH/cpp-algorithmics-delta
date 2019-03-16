#include <bits/stdc++.h>

using namespace std;

#define GRAPH_DATA vector<uint32_t>& parent, const vector<vector<uint32_t>>& graph
void dfs_root(uint32_t u, GRAPH_DATA)
{
    for(uint32_t v : graph[u])
        if(v != parent[u])
            parent[v] = u, dfs_root(v, parent, graph);
}

vector<uint32_t> end_cache;
uint32_t max_path_end(uint32_t u, bool init, GRAPH_DATA)
{
    const uint32_t no = u + (init ? graph.size() : 0);
    if(end_cache[no] != -1u)
        return end_cache[no];

    uint32_t result = 0;
    const uint32_t deg = graph[u].size() - 1;

    if(not init)
        result = max(result, deg);
    for(uint32_t v : graph[u])
        if(v != parent[u])
            result = max(result, max_path_end(v, false, parent, graph) + deg - 1);

    return end_cache[no] = result;
}

vector<uint32_t> cross_cache;
uint32_t max_path_cross(uint32_t u, GRAPH_DATA)
{
    if(cross_cache[u] != -1u)
        return cross_cache[u];

    uint32_t result = 0;
    const uint32_t deg = graph[u].size() - 1;

    vector<uint32_t> paths; paths.reserve(deg);
    for(uint32_t v : graph[u])
        if(v != parent[u])
            paths.push_back(max_path_end(v, false, parent, graph));

    if(deg >= 1)
        result = max(result, max_path_end(u, true, parent, graph));
    if(deg >= 2)
    {
        nth_element(paths.begin(), paths.end() - 2, paths.end());
        result = max(result, paths.end()[-1] + paths.end()[-2] + deg - 2);
    }

    return cross_cache[u] = result;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<uint32_t> parent(n);
    parent[0] = -1u;
    dfs_root(0, parent, graph);

    end_cache.resize(2*n, -1u); cross_cache.resize(n, -1u);

    uint32_t result = 0;
    const uint32_t deg = graph[0].size();
    vector<uint32_t> paths; paths.reserve(deg);
    for(uint32_t v : graph[0])
    {
        paths.push_back(max_path_end(v, false, parent, graph));
        result = max(result, paths.back() + deg - 1);
    }
    if(paths.size() >= 2)
    {
        nth_element(paths.begin(), paths.end() - 2, paths.end());
        result = max(result, paths.end()[-1] + paths.end()[-2] + deg - 2);
    }
    for(uint32_t u = 1; u < n; u++) if(graph[u].size() > 1)
        result = max(result, max_path_cross(u, parent, graph) + 1);
    cout << result;
}
