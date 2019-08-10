#include <bits/stdc++.h>

// -*- ktl/graph/kosaraju.cpp -*-

#include <cstddef>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple> 

using std::size_t;
using std::vector; using std::reverse;
using std::pair; using std::tie;

struct kosaraju
{
    using graph_t = vector<vector<size_t>>;

    const graph_t& graph;
    size_t n;
    vector<bool> vis;

    kosaraju(const graph_t& _graph) : graph(_graph), n(graph.size()), vis(n) {}

    void marker_dfs(size_t u, const graph_t& G, vector<size_t>& out)
    {
        vis[u] = true;
        for(size_t v : G[u])
            if(not vis[v])
                marker_dfs(v, G, out);
        out.push_back(u);
    }

    pair<vector<vector<size_t>>, vector<size_t>>
    operator() ()
    {
        vector<size_t> order; order.reserve(n);
        fill(vis.begin(), vis.end(), false);
        for(size_t u = 0; u < n; u++)
            if(not vis[u])
                marker_dfs(u, graph, order);

        graph_t graph_T(n);
        for(size_t u = 0; u < n; u++)
            for(size_t v : graph[u])
                graph_T[v].push_back(u);

        fill(vis.begin(), vis.end(), false);
        reverse(order.begin(), order.end());
        vector<vector<size_t>> scc;
        vector<size_t> scc_idx(n);
        for(size_t u : order)
        {
            if(vis[u]) continue;
            scc.emplace_back();
            marker_dfs(u, graph_T, scc.back());
            for(auto i : scc.back())
                scc_idx[i] = scc.size() - 1;
        }
        return {scc, scc_idx};
    }

    graph_t make_scc_graph(const vector<vector<size_t>>& scc, const vector<size_t>& scc_idx)
    {
        fill(vis.begin(), vis.end(), false);
        graph_t scc_graph(scc.size());
        for(size_t i = 0; i < scc.size(); i++)
        {
            vis[i] = true;
            for(auto u : scc[i])
              for(auto v : graph[u])
                if(not vis[scc_idx[v]])
            {
                vis[scc_idx[v]] = true;
                scc_graph[i].push_back(scc_idx[v]);
            }
            vis[i] = false;
            for(auto e : scc_graph[i])
                vis[e] = false;
        }
        return scc_graph;
    }
    
    graph_t make_scc_graph()
    {
        vector<vector<size_t>> scc;
        vector<size_t> scc_idx;
        tie(scc, scc_idx) = operator() ();
        return make_scc_graph(scc, scc_idx);
    }
};

// -$- ktl/graph/kosaraju.cpp -$-


using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, p;
    cin >> n >> p;

    vector<uint> direct_bribe(n, UINT_MAX);
    for(size_t i = 0; i < p; i++)
    {
        size_t u; uint c;
        cin >> u >> c; u--;
        direct_bribe[u] = c;
    }

    size_t m;
    cin >> m;

    vector<vector<size_t>> direct_graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        direct_graph[u].push_back(v);
    }

    auto pscc = kosaraju{direct_graph}();
    auto scc = pscc.first; auto scc_index = pscc.second;
    auto graph = kosaraju{direct_graph}.make_scc_graph();

    const size_t s = scc.size();

    vector<uint> bribe(s, UINT_MAX);
    for(size_t i = 0; i < s; i++)
        for(size_t u : scc[i])
            bribe[i] = min(bribe[i], direct_bribe[u]);

    vector<size_t> indegree(s);
    for(size_t u = 0; u < s; u++)
        for(size_t v : graph[u])
            indegree[v]++;

    vector<size_t> critical;
    critical.reserve(s);

    vector<bool> done(s);

    function<void(size_t)> dfs_visit = [&](size_t u) {
        if(done[u]) return;
        done[u] = true;
        for(size_t v : graph[u])
            dfs_visit(v);
    };

    uint cost = 0;

    for(size_t u = s; u --> 0; )
    {
        if(not indegree[u])
        {
            if(bribe[u] == UINT_MAX)
            {
                cout << "NIE\n" << scc[u][0]+1;
                return 0;
            }
            critical.push_back(u);
            cost += bribe[u];
            dfs_visit(u);
        }
    }

    cout << "TAK\n" << cost;
}
