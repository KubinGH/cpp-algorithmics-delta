#include <bits/stdc++.h>

using namespace std;

template<typename Graph>
struct kosaraju
{
    size_t n;
    const Graph &G, &Gt;
    vector<bool> vis;
    kosaraju(size_t n, const Graph& G, const Graph& Gt) : n(n), G(G), Gt(Gt)
        { vis.resize(n, false); }
    void marker_dfs(uint32_t u, vector<uint32_t>& marker, const Graph& g)
    {
        for(uint32_t v : g[u])
            if(not vis[v])
                vis[v] = true, marker_dfs(v, marker, g);
        marker.push_back(u);
    }
    vector<vector<uint32_t>> find_strongly_connected_components()
    {
        vector<uint32_t> order;
        fill(vis.begin(), vis.end(), false);
        for(uint32_t u = 0; u < n; u++)
            if(not vis[u])
                vis[u] = true, marker_dfs(u, order, G);
        reverse(order.begin(), order.end());
        fill(vis.begin(), vis.end(), false);
        vector<vector<uint32_t>> scc;
        for(uint32_t u : order)
        {
            if(vis[u]) continue;
            scc.emplace_back();
            vis[u] = true;
            marker_dfs(u, scc.back(), Gt);
        }
        return scc;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<uint32_t>> G(n), Gt(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v); Gt[v].push_back(u);
    }
    auto scc = kosaraju<decltype(G)>(n, G, Gt).find_strongly_connected_components();
    vector<uint32_t> S(n);
    for(uint32_t i = 0; i < scc.size(); i++)
        for(uint32_t u : scc[i])
            S[u] = i;
    vector<vector<uint32_t>> GS(scc.size()), GSt(scc.size());
    vector<bool> U(scc.size());
    for(uint32_t i = 0; i < scc.size(); i++)
    {
        for(uint32_t u : scc[i])
        {
            for(uint32_t v : G[u])
            {
                if(S[v] != i and not U[S[v]])
                {
                    U[S[v]] = true;
                    GS[i].push_back(S[v]);
                    GSt[S[v]].push_back(i);
                }
            }
        }
        for(uint32_t j : GS[i])
            U[j] = false;
    }
    auto one_way_solve = [&scc](const vector<vector<uint32_t>>& G) {
        vector<uint32_t> T, L, I(G.size()), P(G.size());
        T.reserve(G.size()); L.reserve(G.size());
        for(uint32_t u = 0; u < G.size(); u++)
            for(uint32_t v : G[u])
                I[v]++;
        for(uint32_t u = 0; u < G.size(); u++)
            if(I[u] == 0)
                T.push_back(u);
        for(uint32_t i = 0; i < T.size(); i++)
        {
            uint32_t u = T[i];
            P[u] = i;
            for(uint32_t v : G[u])
                if(--I[v] == 0)
                    T.push_back(v);
        }
        uint32_t x = 0;
        for(uint32_t u : T)
        {
            if(x <= P[u])
            {
                for(uint32_t w : scc[u])
                    L.push_back(w);
            }
            uint32_t k = -1u;
            for(uint32_t v : G[u])
                k = min(k, P[v]);
            x = max(x, k);
        }
        sort(L.begin(), L.end());
        return L;
    };
    vector<uint32_t> A = one_way_solve(GS), B = one_way_solve(GSt), C;
    C.reserve(n);
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(C));
    cout << C.size() << "\n";
    for(uint32_t u : C)
        cout << u+1 << " ";
}
