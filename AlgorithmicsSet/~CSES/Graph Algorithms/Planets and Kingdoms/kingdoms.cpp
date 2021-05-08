#include <bits/stdc++.h>

using namespace std;

struct kosaraju
{
    const vector<vector<size_t>>& graph;
    vector<bool> vis, take;

    kosaraju(const vector<vector<size_t>>& g) : graph(g) {}

    void marker_dfs(size_t u, const vector<vector<size_t>>& G, vector<size_t>& out)
    {
        if(vis[u])
            return;
        vis[u] = true;
        for(auto v : G[u])
            marker_dfs(v, G, out);
        out.push_back(u);
    }

    tuple<vector<size_t>, vector<vector<size_t>>, vector<vector<size_t>>> operator() ()
    {
        const size_t n = graph.size();

        vis.assign(n, false);
        vector<size_t> order;
        for(size_t u = 0; u < n; u++)
            marker_dfs(u, graph, order);
        reverse(order.begin(), order.end());

        vector<vector<size_t>> hparg(n);
        for(size_t u = 0; u < n; u++)
            for(auto v : graph[u])
                hparg[v].push_back(u);

        vis.assign(n, false); take.assign(n, false);
        vector<vector<size_t>> scc, scc_graph;
        vector<size_t> scc_index(n, SIZE_MAX);
        for(auto s : order) if(not vis[s])
        {
            const size_t i = scc.size();
            scc.emplace_back();
            marker_dfs(s, hparg, scc.back());
            for(auto u : scc.back())
                scc_index[u] = i;
        }
        for(size_t i = 0; i < scc.size(); i++)
        {
            take[i] = true;
            scc_graph.emplace_back();
            for(auto u : scc.back())
                for(auto v : graph[u])
                    if(not take[scc_index[v]])
                        take[scc_index[v]] = true, scc_graph[i].push_back(scc_index[v]);
            take[i] = false;
            for(auto j : scc_graph[i])
                take[j] = false;
        }

        return {scc_index, scc, scc_graph};
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }

    auto [scc_index, scc, scc_graph] = kosaraju{graph}();

    cout << scc.size() << endl;
    for(size_t u = 0; u < n; u++)
        cout << 1 + scc_index[u] << ' ';
    cout << endl;
}
