#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static array<vector<uint32_t>, MAX> G;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    static array<bool, MAX> V;
    static array<uint32_t, MAX> R;
    queue<pair<uint32_t, uint32_t>> Q;
    V[0] = true;
    Q.emplace(0, 0);
    while(not Q.empty())
    {
        pair<uint32_t, uint32_t> c = Q.front(); Q.pop();;
        uint32_t u = c.first, d = c.second;
        for(uint32_t v : G[u])
        {
            if(not V[v])
            {
                V[v] = true;
                Q.emplace(v, d + 1);
                R[v] = d + 1;
            }
        }
    }
    for(uint32_t i = 0; i < n; i++)
    {
        if(i == 0 or R[i] != 0)
            cout << R[i] << '\n';
        else
            cout << "-1\n";
    }
}
