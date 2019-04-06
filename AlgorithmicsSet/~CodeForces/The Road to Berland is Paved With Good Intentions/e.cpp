#include <bits/stdc++.h>

using namespace std;

struct kosaraju
{
    using graph_t = vector<vector<size_t>>;
    size_t n;
    vector<bool> vis;

    kosaraju(size_t _n) : n(_n), vis(n) {}

    void marker_dfs(size_t u, const graph_t& graph, vector<uint32_t>& out)
    {
        vis[u] = true;
        for(size_t v : graph[u])
            if(not vis[v])
                marker_dfs(v, graph, out);
        out.push_back(u);
    }

    // Returns a list of strongly connected components, and
    // a list containing which SCC does a vertex belong to.
    pair<vector<vector<size_t>>, vector<size_t>>
    operator() (const graph_t& graph)
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
};

struct solver_2sat
{
    size_t n;
    vector<vector<size_t>> imp_graph;

    solver_2sat(size_t _n) : n(_n), imp_graph(2*n) {}

    static constexpr size_t as_index(int32_t p)
    {
        return p < 0 ? 2*(-p-1) + 1 : 2*(p-1);
    }

    void add_implication(int32_t a, int32_t b)
    {
        imp_graph[as_index(a)].push_back(as_index(b));
    }
    void add_force_true(int32_t a)
    {
        add_implication(-a, a);
    }
    void add_or_clause(int32_t a, int32_t b)
    {
        add_implication(-a, b);
        add_implication(-b, a);
    }
    void add_xnor_clause(int32_t a, int32_t b)
    {
        add_or_clause(a, -b);
        add_or_clause(-a, b);
    }
    void add_xor_clause(int32_t a, int32_t b)
    {
        add_or_clause(a, b);
        add_or_clause(-a, -b);
    }

    struct solution_2sat { bool exists; vector<bool> value; };
    solution_2sat solve()
    {
        auto pscc = kosaraju{2*n}(imp_graph);
        auto scc = pscc.first; auto scc_idx = pscc.second;
        const size_t s = scc.size();
        for(size_t u = 0; u < 2*n; u += 2)
        {
            if(scc_idx[u] == scc_idx[u^1])
                return {false, {}};
        }

        vector<bool> is_set(s), truth_value(s);

        for(size_t u = s; u --> 0; )
        {
            if(not is_set[u])
            {
                is_set[u] = true, truth_value[u] = true;
                for(size_t i : scc[u])
                {
                    size_t v = scc_idx[i^1];
                    is_set[v] = true; truth_value[v] = false;
                }
            }
        }
        vector<bool> out(n);
        for(size_t i = 0; i < n; i++)
            out[i] = truth_value[scc_idx[2*i]];
        return {true, out};
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    solver_2sat SAT(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v; bool t;
        cin >> u >> v >> t;
        if(t)
            SAT.add_xnor_clause(u, v);
        else
            SAT.add_xor_clause(u, v);
    }
    auto solution = SAT.solve();
    if(not solution.exists)
        cout << "Impossible";
    else
    {
        vector<uint32_t> result; result.reserve(n);
        for(uint32_t i = 0; i < n; i++)
            if(solution.value[i])
                result.push_back(i+1);
        cout << result.size() << endl;
        for(auto x : result)
            cout << x << " ";
    }
}
