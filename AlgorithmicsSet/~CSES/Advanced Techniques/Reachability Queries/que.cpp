#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#pragma GCC target ("popcnt,avx,avx2")

using namespace std;

struct kosaraju
{
    const vector<vector<size_t>>& graph;
    vector<bool> vis;

    kosaraju(const vector<vector<size_t>>& G) : graph(G) {}

    void marker_dfs(size_t u, vector<size_t>& out, const vector<vector<size_t>>& G)
    {
        if(vis[u])
            return;
        vis[u] = true;
        for(auto v : G[u])
            marker_dfs(v, out, G);
        out.push_back(u);
    }

    pair<vector<size_t>, vector<vector<size_t>>> operator()()
    {
        const size_t n = graph.size();
        vector<vector<size_t>> hparg(n);
        for(size_t u = 0; u < n; u++)
            for(auto v : graph[u])
                hparg[v].push_back(u);

        vis.assign(n, false);
        vector<size_t> order;
        for(size_t u = 0; u < n; u++)
            marker_dfs(u, order, graph);
        reverse(order.begin(), order.end());

        vis.assign(n, false);
        vector<size_t> scc_index(n, SIZE_MAX);
        vector<vector<size_t>> scc, scc_graph;
        for(auto u : order)
        {
            if(vis[u])
                continue;
            const size_t s = scc_graph.size();
            scc.emplace_back();
            scc_graph.emplace_back();
            marker_dfs(u, scc.back(), hparg);
            for(auto v : scc.back())
                scc_index[v] = s;
        }

        vis.assign(n, false);
        for(size_t s = 0; s < scc.size(); s++)
        {
            vis[s] = true;
            for(auto v : scc[s])
            {
                for(auto w : graph[v])
                {
                    auto z = scc_index[w];
                    if(not vis[z])
                        vis[z] = true, scc_graph[s].push_back(z);
                }
            }
            vis[s] = false;
            for(auto z : scc_graph[s])
                vis[z] = false;
        }
        return {scc_index, scc_graph};
    }
};

constexpr size_t word_size = 4096;
using word_t = bitset<word_size>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n1, m, q;
    cin >> n1 >> m >> q;

    vector<vector<size_t>> graph(n1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }

    auto [scc_index, scc_graph] = kosaraju{graph}();
    const size_t n = scc_graph.size();

    vector<pair<size_t, size_t>> queries(q);
    vector<bool> answer(q);

    for(size_t i = 0; i < q; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        queries[i] = {scc_index[u], scc_index[v]};
    }


    vector<word_t> words(n);
    for(size_t k = 0; k*word_size < n; k++)
    {
        for(size_t u = n; u --> 0; )
        {
            words[u].reset();
            for(auto v : scc_graph[u])
                words[u] |= words[v];
            if(u >= k*word_size and u < (k+1)*word_size)
                words[u].set(u % word_size);
        }
        for(size_t i = 0; i < q; i++)
        {
            auto [u, v] = queries[i];
            if(v >= k*word_size and v < (k+1)*word_size)
                answer[i] = words[u][v % word_size];
        }
    }

    for(size_t i = 0; i < q; i++)
        cout << (answer[i] ? "YES" : "NO") << '\n';
}
