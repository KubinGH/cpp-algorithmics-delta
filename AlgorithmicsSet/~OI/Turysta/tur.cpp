#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 11;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    mt19937 gen(time(0));

    vector<bitset<MAX>> conn(n);

    for(size_t i = 1; i < n; i++)
      for(size_t j = 0; j < i; j++)
    {
        bool e;
        cin >> e;
        (e ? conn[j][i] : conn[i][j]) = true;
    }
    cerr << "read done" << endl;

    // find reach bitmap (for SCC)
    vector<bitset<MAX>> reach(n);
    for(size_t s = 0; s < n; s++)
    {
        function<void(size_t)> dfs = [&](size_t u) {
            reach[s][u] = true;
            for(size_t v = 0; v < n; v++) if(conn[u][v] and not reach[s][v])
                dfs(v);
        };
        dfs(s);
    }
    cerr << "reach done" << endl;

    vector<bool> has_scc(n);
    vector<vector<size_t>> scc;

    for(size_t s = 0; s < n; s++) if(not has_scc[s])
    {
        vector<bool> this_scc(n);
        // find scc
        this_scc[s] = has_scc[s] = true;
        scc.push_back({s});
        for(size_t v = 0; v < n; v++)
            if(not has_scc[v] and reach[s][v] and reach[v][s])
                scc.back().push_back(v), this_scc[v] = has_scc[v] = true;

        if(scc.back().size() == 1)
            continue;

        // find any cycle
        vector<bool> vis(n), stk(n);
        vector<size_t> cycle;
        function<int(size_t)> dfs = [&](size_t v) -> int {
            vis[v] = stk[v] = true;
            for(size_t w = 0; w < n; w++) if(this_scc[w] and conn[v][w])
            {
                if(not vis[w])
                {
                    auto d = dfs(w);
                    if(d >= 0)
                        cycle.push_back(v);
                    if(d != -1)
                        return (size_t)d == v ? -2 : d;
                }
                else if(stk[w])
                {
                    cycle.push_back(v);
                    return w;
                }
            }
            stk[v] = false;
            return -1;
        };
        dfs(s);

        assert(not cycle.empty());
        reverse(cycle.begin(), cycle.end());

        // build the rest of the hamiltonian cycle in the SCC
        while(cycle.size() < scc.back().size())
        {
            shuffle(scc.back().begin(), scc.back().end(), gen);
            for(auto u : scc.back())
            {
                if(find(cycle.begin(), cycle.end(), u) != cycle.end()) continue;

                cycle.push_back(cycle.front());
                for(size_t i = 0; i+1 < cycle.size(); i++)
                {
                    if(conn[cycle[i]][u] and conn[u][cycle[i+1]])
                    {
                        cycle.insert(cycle.begin() + (i+1), u);
                        break;
                    }
                }
                cycle.pop_back();
            }
        }

        // we want to keep this cycle as an ordering
        scc.back() = cycle;
    }
    cerr << "cycles done" << endl;

    sort(scc.begin(), scc.end(), [&](const vector<size_t>& a, const vector<size_t>& b) {
        return conn[a[0]][b[0]];
    });

    vector<size_t> of_scc(n, SIZE_MAX);
    for(size_t s = 0; s < scc.size(); s++)
        for(auto u : scc[s])
            of_scc[u] = s;
    cerr << "prep done" << endl;

    for(size_t u = 0; u < n; u++)
    {
        vector<size_t> path = scc[of_scc[u]];
        rotate(path.begin(), find(path.begin(), path.end(), u), path.end());
        for(size_t s = of_scc[u]+1; s < scc.size(); s++)
            path.insert(path.end(), scc[s].begin(), scc[s].end());

        cout << path.size() << ' ';
        for(auto v : path)
            cout << v+1 << ' ';
        cout << '\n';
    }

}
