#include <bits/stdc++.h>

using namespace std;

typedef pair<uint32_t, uint32_t> pair_u32;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, x;
    cin >> n >> m >> x;
    static array<vector<pair<uint32_t, bool>>, MAX> G;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v, c;
        cin >> u >> v >> c; u--; v--;
        bool b = c != 0;
        G[u].emplace_back(v, b);
    }
    static array<uint32_t, MAX> D;
    D.fill(-1u); D[0] = 0;
    priority_queue<pair_u32, vector<pair_u32>, greater<pair_u32>> Q;
    Q.emplace(0, 0);
    while(not Q.empty())
    {
        pair<uint32_t, uint32_t> cp = Q.top(); Q.pop();
        uint32_t u = cp.second, d = cp.first;
        if(d > D[u])
            continue;
        else if(u == n - 1)
            break;
        for(pair_u32 e : G[u])
        {
            uint32_t v = e.first; bool b = e.second;
            if(D[u] + b < D[v])
            {
                D[v] = D[u] + b;
                Q.emplace(D[v], v);
            }
        }
    }
    if(D[n-1] != -1u)
        cout << (uint64_t)D[n-1] * (uint64_t)x;
    else
        cout << "NIE";
}
