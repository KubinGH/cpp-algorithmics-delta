#include <bits/stdc++.h>

using namespace std;

struct kosaraju
{
    using graph_t = vector<vector<uint32_t>>;
    const graph_t& graph;
    uint32_t n;
    vector<bool> vis;
    kosaraju(const graph_t& _graph) : graph(_graph), n(graph.size()), vis(n) {}

    void marker_dfs(uint32_t u, const vector<vector<uint32_t>>& G, vector<uint32_t>& out)
    {
        vis[u] = true;
        for(uint32_t v : G[u])
            if(not vis[v])
                marker_dfs(v, G, out);
        out.push_back(u);
    }

    pair<vector<uint32_t>, vector<vector<uint32_t>>> operator() ()
    {
        fill(vis.begin(), vis.end(), false);
        vector<uint32_t> order; order.reserve(n);
        for(uint32_t u = 0; u < n; u++)
            if(not vis[u])
                marker_dfs(u, graph, order);
        reverse(order.begin(), order.end());

        graph_t hparg(n);
        for(uint32_t u = 0; u < n; u++)
            for(uint32_t v : graph[u])
                hparg[v].push_back(u);

        fill(vis.begin(), vis.end(), false);
        vector<vector<uint32_t>> scc;
        vector<uint32_t> scc_idx(n);
        for(uint32_t u : order)
        {
            if(vis[u]) continue;
            scc.emplace_back();
            marker_dfs(u, hparg, scc.back());
            for(uint32_t v : scc.back())
                scc_idx[v] = scc.size() - 1;
        }

        return make_pair(scc_idx, scc);
    }
};

struct solver_2sat
{
    uint32_t n;
    vector<vector<uint32_t>> imp_graph;
    solver_2sat(uint32_t _n) : n(_n), imp_graph(2*n) {}

    void add_implication(uint32_t u, uint32_t v)
    {
        imp_graph[u].push_back(v);
    }
    void add_or_clause(uint32_t u, uint32_t v)
    {
        add_implication(u^1, v);
        add_implication(v^1, u);
    }
    bool operator() ()
    {
        auto pscc = kosaraju{imp_graph}();
        auto scc_idx = pscc.first; auto scc = pscc.second;

        for(uint32_t i = 0; i < n; i++)
            if(scc_idx[2*i] == scc_idx[2*i+1])
                return false;

        return true;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    while(t --> 0)
    {
        uint32_t n, _;
        cin >> n >> _;
        vector<uint32_t> A(n);
        for(uint32_t i = 0; i < n; i++)
            cin >> A[i];

        solver_2sat SAT(n-1);

        map<pair<uint32_t, uint32_t>, vector<uint32_t>> occ;
        for(uint32_t i = 0; i+1 < n; i++)
            occ[{A[i], A[i+1]}].push_back(i);

        SAT.add_or_clause(2*0, 2*0);
        for(uint32_t i = 1; i+1 < n-1; i++)
        {
            SAT.add_or_clause(2*(i-1), 2*i);
            SAT.add_or_clause(2*i, 2*(i+1));
        }
        SAT.add_or_clause(2*(n-2), 2*(n-2));

        for(auto kv : occ)
        {
            auto k = kv.first; const auto& v = kv.second;
            for(uint32_t i = 0; i < v.size(); i++)
                for(uint32_t j = i+1; j < v.size(); j++)
            {
                SAT.add_implication(2*v[i], 2*v[j]+1);
                SAT.add_implication(2*v[j], 2*v[i]+1);
            }
        }

        cout << (SAT() ? "TAK" : "NIE") << endl;
        continue;
    force_false:
        cout << "NIE" << endl;
    }
}