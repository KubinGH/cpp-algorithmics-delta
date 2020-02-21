#include <bits/stdc++.h>

using namespace std;

struct kosaraju
{
    using graph_t = vector<vector<size_t>>;

    const size_t n;
    const graph_t& graph;
    vector<bool> vis;
    graph_t hparg;

    kosaraju(const graph_t& G) : n(G.size()), graph(G), vis(n), hparg(n)
    {
        for(size_t u = 0; u < n; u++)
            for(size_t v : graph[u])
                hparg[v].push_back(u);
    }

    void marker(size_t u, const graph_t& G, vector<size_t>& out)
    {
        if(vis[u]) return;
        vis[u] = true;
        for(size_t v : G[u])
            marker(v, G, out);
        out.push_back(u);
    }

    struct scc_data
    {
        vector<size_t> index;
        vector<vector<size_t>> vertices, graph;
    };

    scc_data operator() ()
    {
        fill(vis.begin(), vis.end(), false);
        vector<size_t> order; order.reserve(n);
        for(size_t u = 0; u < n; u++)
            marker(u, graph, order);

        vector<vector<size_t>> scc;
        vector<size_t> scc_idx(n);
        fill(vis.begin(), vis.end(), false);
        reverse(order.begin(), order.end());
        for(size_t u : order) if(not vis[u])
        {
            scc.emplace_back();
            marker(u, hparg, scc.back());
            for(auto v : scc.back())
                scc_idx[v] = scc.size() - 1;
        }

        graph_t scc_graph(scc.size());
        fill(vis.begin(), vis.end(), false);
        for(size_t i = 0; i < scc.size(); i++)
        {
            vis[i] = true;
            for(size_t u : scc[i])
            {
                for(size_t v : graph[u])
                {
                    size_t j = scc_idx[v];
                    if(i != j and not vis[j])
                        vis[j] = true, scc_graph[i].push_back(j);
                }
            }
            vis[i] = false;
            for(size_t j : scc_graph[i])
                vis[j] = false;
        }

        return {scc_idx, scc, scc_graph};
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

    auto scc = kosaraju{graph}();
    size_t k = scc.vertices.size();

    vector<size_t> indeg(k);
    for(size_t u = 0; u < k; u++)
        for(auto v : scc.graph[u])
            indeg[v]++;

    vector<size_t> src;
    for(size_t u = 0; u < k; u++)
        if(not indeg[u])
            src.push_back(u);

    if(src.size() == 1)
    {
        auto vec = scc.vertices[src[0]];
        sort(vec.begin(), vec.end());
        cout << vec.size() << endl;
        for(auto u : vec)
            cout << u+1 << ' ';
        cout << endl;
    }
    else
        cout << '0' << endl;

}
