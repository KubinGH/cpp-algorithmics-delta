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

    tuple<vector<size_t>, vector<vector<size_t>>> operator() ()
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

        return {scc_index, scc};
    }
};

struct sat_solver
{
    vector<vector<size_t>> imp;

    sat_solver(size_t n) : imp(2*n) {}

    size_t var()
    {
        imp.emplace_back(); imp.emplace_back();
        return imp.size() / 2 - 1;
    }

    static constexpr size_t index(int i)
    {
        return i > 0 ? 2*(i - 1) : 2*(-i - 1) + 1;
    }

    void _or_clause(size_t u, size_t v)
    {
        imp[u^1].push_back(v);
        imp[v^1].push_back(u);
    }
    void or_clause(int p, int q) { return _or_clause(index(p), index(q)); }

    vector<bool> operator() ()
    {
        const size_t n = imp.size() / 2;
        auto [scc_index, scc] = kosaraju{imp}();
        vector<bool> result(n + 1);
        for(size_t i = 0; i < n; i++)
        {
            if(scc_index[2*i] == scc_index[2*i + 1])
                return {};
            result[i + 1] = scc_index[2*i] > scc_index[2*i + 1];
        }
        return result;
    }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    sat_solver sat(m);
    for(size_t i = 0; i < n; i++)
    {
        char A, B; int a, b;
        cin >> A >> a >> B >> b;
        if(A == '-') a = -a;
        if(B == '-') b = -b;
        sat.or_clause(a, b);
    }

    auto truth = sat();
    if(not truth.empty())
    {
        for(size_t i = 1; i <= m; i++)
            cout << (truth[i] ? '+' : '-') << ' ';
        cout << endl;
    }
    else
        cout << "IMPOSSIBLE" << endl;
}
