#include <bits/stdc++.h>

using namespace std;

void dfs(size_t u, const vector<vector<size_t>>& graph, vector<bool>& vis, vector<size_t>& out)
{
    if(vis[u])
        return;
    vis[u] = true;
    out.push_back(u);
    for(auto v : graph[u])
        dfs(v, graph, vis, out);
}

vector<vector<size_t>> components(const vector<vector<size_t>>& graph)
{
    vector<vector<size_t>> r;
    vector<bool> vis(graph.size());
    for(size_t u = 0; u < graph.size(); u++)
        if(not vis[u])
            r.emplace_back(), dfs(u, graph, vis, r.back());
    return r;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<size_t> indeg(n);
    vector<vector<size_t>> graph(n), wgraph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        indeg[v]++;
        graph[u].push_back(v);
        wgraph[u].push_back(v);
        wgraph[v].push_back(u);
    }

    size_t result = 0;
    for(auto comp : components(wgraph))
    {
        vector<size_t> zero;
        zero.reserve(n);

        for(size_t u : comp)
            if(not indeg[u])
                zero.push_back(u);

        size_t loop = 0;
        while(not zero.empty())
        {
            auto u = zero.back(); zero.pop_back();
            for(auto v : graph[u])
                if(not --indeg[v])
                    zero.push_back(v);
            loop++;
        }

        const size_t v = comp.size();
        result += v - (loop == v);
    }

    cout << result;
}
