#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 16;

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
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
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
    static uint32_t comp_id[MAX], curr_id = 0, s = 0;
    for(auto comp : strong_components)
    {
        for(uint32_t u : comp)
            comp_id[u] = curr_id;
        curr_id++;
    }
    static vector<uint32_t> strgraph[MAX];
    s = curr_id; curr_id = 0;
    static uint32_t enters[MAX];
    for(auto comp : strong_components)
    {
        static bitset<MAX> conn;
        for(uint32_t u : comp)
        {
            for(uint32_t v : graph[u])
            {
                if(curr_id != comp_id[v] and not conn[comp_id[v]])
                {
                    conn[comp_id[v]] = true;
                    strgraph[curr_id].push_back(comp_id[v]);
                    enters[comp_id[v]]++;
                }
            }
        }
        for(uint32_t v : strgraph[curr_id])
            conn[v] = false;
        curr_id++;
    }
    vector<uint32_t> topo; topo.reserve(s);
    for(uint32_t u = 0; u < s; u++)
    {
        if(enters[u] == 0)
            topo.push_back(u);
    }
    for(uint32_t i = 0; i < topo.size(); i++)
    {
        uint32_t u = topo[i];
        for(uint32_t v : strgraph[u])
        {
            enters[v]--;
            if(enters[v] == 0)
                topo.push_back(v);
        }
    }
    reverse(topo.begin(), topo.end());
    static uint32_t result[MAX];
    for(uint32_t u : topo)
    {
        result[u] = strong_components[u].size();
        for(uint32_t v : strgraph[u])
            result[u] += result[v];
    }
    for(uint32_t i = 0; i < n; i++)
        cout << result[comp_id[i]]-1 << "\n";
}
