#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using graph_t = vector<vector<uint32_t>>;

pair<bool, vector<uint32_t>> solve(graph_t& G, uint32_t k)
{
    const uint32_t n = G.size();
    uint32_t U = -1u;
    for(uint32_t u = 0; u < n; u++)
      if(G[u].size() >= 3)
        { U = u; break; }
    if(U != -1u)
    {
        if(k == 0)
            return {false, {}};
        uint32_t C[4] = {U, G[U][0], G[U][1], G[U][2]};
        for(uint32_t i = 0; i < 4; i++)
        {
            uint32_t u = C[i];
            vector<uint32_t> E;
            E.swap(G[u]);
            for(auto v : E)
            {
                iter_swap(find(G[v].begin(), G[v].end(), u), --G[v].end());
                G[v].pop_back();
            }
            auto solution = solve(G, k-1);
            if(solution.first)
            {
                solution.second.push_back(u);
                return solution;
            }
            G[u].swap(E);
            for(auto v : G[u])
                G[v].push_back(u);
        }
        return {false, {}};
    }
    else
    {
        vector<bool> V(n);
        vector<uint32_t> R;
        for(uint32_t s = 0; s < n; s++) if(not V[s])
        {
            bool all2 = true;
            stack<uint32_t> S;
            S.push(s); V[s] = true;
            while(not S.empty())
            {
                uint32_t u = S.top(); S.pop();
                if(G[u].size() < 2)
                    all2 = false;
                for(uint32_t v : G[u])
                    if(not V[v])
                        S.push(v), V[v] = true;
            }
            if(all2)
                R.push_back(s);
        }
        if(R.size() <= k)
            return {true, R};
        else
            return {false, {}};
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k; k = min(k, n);
    graph_t G(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    auto o_solution = solve(G, k);
    if(o_solution.first)
    {
        cout << "TAK\n";
        auto solution = o_solution.second;
        cout << solution.size() << "\n";
        for(uint32_t u : solution)
            cout << u+1 << " ";
    }
    else
        cout << "NIE";
}
