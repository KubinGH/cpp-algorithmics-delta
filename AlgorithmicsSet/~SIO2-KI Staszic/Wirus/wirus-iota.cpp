#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 20, MAX_E = 1 << 19;

struct pairhash
{
    size_t operator() (const pair<uint32_t, uint32_t>& p) const
    {
        return uint64_t(p.first) * uint64_t(p.second) + (p.first ^ p.second);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t k;
    cin >> k;
    vector<pair<uint32_t, uint32_t>> E(k);
    static unordered_set<uint32_t> G[MAX_E];
    for(uint32_t i = 0; i < k; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        E[i] = {u, v};
        G[u].emplace(i);
        G[v].emplace(i);
    }
    for(uint32_t u = 0; u < MAX_E; u++)
    {
        if(G[u].size() % 2)
        {
            cout << "NIE\n";
            return 0;
        }
    }

    vector<bool> U(k);
    for(uint32_t s = 0; s < MAX_E; s++) while(not G[s].empty())
    {
        uint32_t u = s;
        do {
            if(G[u].empty())
            {
                cout << "NIE\n";
                return 0;
            }
            auto e = *G[u].begin();
            uint32_t v;
            if(E[e].first == u)
                v = E[e].second, U[e] = 0;
            else
                v = E[e].first,  U[e] = 1;
            G[u].erase(e); G[v].erase(e);
            u = v;
        } while(u != s);
    }
    cout << "TAK\n";
    for(uint32_t e = 0; e < k; e++)
        cout << (U[e] ? 'O' : 'Z') << "\n";
}