#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<size_t>>;

struct kosaraju
{
    const size_t n;
    const graph_t& G;
    graph_t G_T;

    vector<bool> vis;

    kosaraju(const graph_t& _G) : n(_G.size()), G(_G), G_T(n), vis(n)
    {
        for(size_t u = 0; u < n; u++)
            for(auto v : G[u])
                G_T[v].push_back(u);
    }

    void marker(size_t u, const graph_t& H, vector<size_t>& out)
    {
        vis[u] = true;
        for(auto v : H[u])
            if(not vis[v])
                marker(v, H, out);
        out.push_back(u);
    }

    pair<vector<vector<size_t>>, vector<size_t>> operator() ()
    {
        fill(vis.begin(), vis.end(), false);
        vector<size_t> order; order.reserve(n);
        for(size_t u = 0; u < n; u++)
            if(not vis[u])
                marker(u, G, order);
        reverse(order.begin(), order.end());

        fill(vis.begin(), vis.end(), false);
        vector<vector<size_t>> scc;
        vector<size_t> scc_idx(n);
        for(size_t u : order)
          if(not vis[u])
        {
            scc.emplace_back();
            marker(u, G_T, scc.back());
            for(auto v : scc.back())
                scc_idx[v] = scc.size() - 1;
        }

        return {scc, scc_idx};
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    graph_t G(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
    }

    auto I = kosaraju{G}().second;
    size_t q;
    cin >> q;

    while(q --> 0)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        cout << (I[u] == I[v] ? "MISJA UDANA\n" : "MISJA NIEUDANA\n");
    }
}
