#include <bits/stdc++.h>
#include <ktl/graph/kosaraju.cpp>

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
