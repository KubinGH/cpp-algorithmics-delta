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

// -*- ktl/general/2sat.cpp -*-

#include <vector>
#include <cstddef>
#include <algorithm>

using std::vector;
using std::size_t;
using std::reverse;

struct solver_2sat
{
    size_t n;
    vector<vector<size_t>> imp_graph;

    solver_2sat(size_t _n) : n(_n), imp_graph(2*n) {}

    static constexpr size_t as_index(int p)
    {
        return p < 0 ? 2*(-p-1) + 1 : 2*(p-1);
    }

    void add_implication(int a, int b)
    {
        imp_graph[as_index(a)].push_back(as_index(b));
    }
    void add_or_clause(int a, int b)
    {
        add_implication(-a, b);
        add_implication(-b, a);
    }
    void add_xnor_clause(int a, int b)
    {
        add_or_clause(a, -b);
        add_or_clause(-a, b);
    }
    void add_xor_clause(int a, int b)
    {
        add_or_clause(a, b);
        add_or_clause(-a, -b);
    }
    void force_true(int a)
    {
        add_or_clause(a, a);
    }
    void force_false(int a)
    {
        return force_true(-a);
    }

    struct solution_2sat { bool exists; vector<bool> value; };
    solution_2sat solve()
    {
        auto pscc = kosaraju{imp_graph}();
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
                is_set[u] = true, truth_value[u] = true;
            for(size_t i : scc[u])
            {
                size_t v = scc_idx[i^1];
                is_set[v] = true; truth_value[v] = not truth_value[u];
            }
        }
        vector<bool> out(n);
        for(size_t i = 0; i < n; i++)
            out[i] = truth_value[scc_idx[2*i]];
        return {true, out};
    }
};

// -$- ktl/general/2sat.cpp -$-


using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<int>> seq(n);
    for(auto& s : seq)
    {
        size_t k;
        cin >> k;
        s.resize(k);
        for(auto& x : s)
            cin >> x;
    }

    auto fail = []() {
        cout << "No" << endl;
        exit(0);
    };

    solver_2sat sat(m);

    for(size_t i = 0; i+1 < n; i++)
    {
        const auto& A = seq[i]; auto a = A.size();
        const auto& B = seq[i+1]; auto b = B.size();

        if(a > b and equal(B.begin(), B.end(), A.begin()))
            fail();
        else if(a <= b and equal(A.begin(), A.end(), B.begin()))
            {}
        else
        {
            auto p = mismatch(A.begin(), A.end(), B.begin());
            auto x = *p.first, y = *p.second;
            if(x < y)
                sat.add_or_clause(x, -y);
            else
                sat.force_true(x), sat.force_false(y);
        }
    }

    auto solution = sat.solve();
    if(solution.exists)
    {
        cout << "Yes" << endl;
        cout << count(solution.value.begin(), solution.value.end(), true) << endl;
        for(size_t i = 0; i < m; i++)
            if(solution.value[i])
                cout << i+1 << ' ';
    }
    else
        fail();
}
