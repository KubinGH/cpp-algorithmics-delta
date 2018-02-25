#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 5000;
const uint16_t INF_U16 = numeric_limits<uint16_t>::max();

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t n, m; uint32_t k;
    cin >> n >> m >> k;
    static vector<uint16_t> G[MAX];
    for(uint16_t i = 0; i < m; i++)
    {
        uint16_t a, b;
        cin >> a >> b; a--; b--;
        G[a].push_back(b); G[b].push_back(a);
    }
    static uint16_t V[MAX][MAX][2];
    for(uint16_t s = 0; s < n; s++)
    {
        static uint16_t D[MAX][2];
        for(uint16_t i = 0; i < n; i++)
            D[i][0] = D[i][1] = INF_U16;
        queue<pair<uint16_t, uint16_t>> Q;
        if(not G[s].empty())
            V[s][s][0] = 2;
        Q.emplace(0, s);
        while(not Q.empty())
        {
            pair<uint16_t, uint16_t> cp = Q.front(); Q.pop();
            uint16_t u = cp.second, d = cp.first;
            if(D[u][d%2] < d)
                continue;
            bool m = d % 2;
            for(uint16_t i = 0; i < G[u].size(); i++)
            {
                uint16_t v = G[u][i];
                if(V[s][v][!m] == 0 or V[s][v][!m] >= d + 1)
                {
                    V[s][v][!m] = d + 1;
                    if(d + 1 < D[v][(d+1)%2])
                        Q.emplace(d + 1, v), D[v][(d+1)%2] = d + 1;
                }
            }
        }
    }
    for(uint32_t ki = 0; ki < k; ki++)
    {
        uint32_t u, v, d;
        cin >> u >> v >> d; u--; v--;
        if(V[u][v][d%2] == 0 or V[u][v][d%2] > d)
            cout << "NIE\n";
        else
            cout << "TAK\n";
    }
}
