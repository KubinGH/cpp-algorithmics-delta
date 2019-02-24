#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<pair<uint32_t, uint32_t>> E(n);
    vector<vector<uint32_t>> G(2*n);
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        E[i] = {u, v};
        G[u].push_back(v);
        G[v].push_back(u);
        G[2*i].push_back(2*i+1);
        G[2*i+1].push_back(2*i);
    }

    vector<bool> V(2*n), F(2*n);
    stack<uint32_t> S;
    for(uint32_t z = 0; z < 2*n; z++) if(not V[z])
    {
        S.push(z); V[z] = true;
        while(not S.empty())
        {
            uint32_t u = S.top(); S.pop();
            for(uint32_t v : G[u])
            {
                if(not V[v])
                {
                    V[v] = true;
                    F[v] = !F[u];
                    S.push(v);
                }
            }
        }
    }
    for(uint32_t i = 0; i < n; i++)
        cout << F[E[i].first]+1 << " " << F[E[i].second]+1 << "\n";
}
