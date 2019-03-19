#include <bits/stdc++.h>

using namespace std;

using graph_t = vector<vector<uint32_t>>;

struct kosaraju
{
    const graph_t& G;
    size_t n;
    graph_t Gt;
    vector<bool> vis;

    void marker_dfs(uint32_t u, const graph_t& G1, vector<uint32_t>& out)
    {
        vis[u] = true;
        for(uint32_t v : G1[u])
            if(not vis[v])
                marker_dfs(v, G1, out);
        out.push_back(u);
    }

    kosaraju(const graph_t& _G) : G(_G), n(G.size()), Gt(n), vis(n)
    {
        for(size_t u = 0; u < n; u++)
            for(size_t v : G[u])
                Gt[v].push_back(u);
    }

    vector<vector<uint32_t>> find_scc()
    {
        fill(vis.begin(), vis.end(), false);

        vector<uint32_t> order; order.reserve(n);
        for(uint32_t u = 0; u < n; u++)
            if(not vis[u])
                marker_dfs(u, G, order);

        reverse(order.begin(), order.end());
        fill(vis.begin(), vis.end(), false);

        vector<vector<uint32_t>> scc;
        for(uint32_t u = 0; u < n; u++)
          if(not vis[u])
        {
            scc.emplace_back();
            marker_dfs(u, Gt, scc.back());
        }

        return scc;
    }
};



int main()
{

}
