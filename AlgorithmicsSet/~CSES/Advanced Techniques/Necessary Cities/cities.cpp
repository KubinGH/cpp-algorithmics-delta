#include <bits/stdc++.h>

using namespace std;

struct low_processor
{
    const size_t n;
    const vector<vector<size_t>>& graph;
    int watch;
    vector<int> preorder, postorder, low;
    vector<size_t> parent;
    vector<bool> vis, stk;
    vector<size_t> articulation;
    vector<pair<size_t, size_t>> bridges;

    low_processor(const vector<vector<size_t>>& _graph)
        : n(_graph.size()), graph(_graph), watch(0),
          preorder(n, -1), postorder(n, -1), low(n, INT_MAX),
          parent(n, SIZE_MAX) {}

    void dfs(size_t u)
    {
        if(vis[u])
            return;
        vis[u] = stk[u] = true;
        low[u] = preorder[u] = watch++;
        for(auto v : graph[u])
        {
            if(not vis[v])
            {
                parent[v] = u;
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if(stk[v] and v != parent[u])
                low[u] = min(low[u], preorder[v]);
        }
        stk[u] = false;
        postorder[u] = watch;

        for(auto v : graph[u])
            if(u == parent[v] and preorder[u] < low[v])
                bridges.emplace_back(u, v);

        for(auto v : graph[u])
            if(u == parent[v] and preorder[u] <= low[v])
                { articulation.push_back(u); break; }
    }

    low_processor& operator()()
    {
        vis.assign(n, false); stk.assign(n, false);
        for(size_t s = 0; s < n; s++)
            dfs(s);
        return *this;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto p = low_processor{graph}();

    cout << p.articulation.size() << endl;
    for(auto u : p.articulation)
        cout << u << ' ';
}
