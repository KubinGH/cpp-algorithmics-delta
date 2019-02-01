#include <bits/stdc++.h>

using namespace std;

const size_t N = 128;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, q;
    cin >> n >> m >> q;
    static uint32_t Q[N][N];
    fill(&Q[0][0], &Q[n][0], (1u << 30));
    for(uint32_t u = 0; u < n; u++)
        Q[u][u] = 0;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w; u--; v--;
        Q[u][v] = Q[v][u] = min(Q[u][v], w);
    }
    for(uint32_t j = 0; j < n; j++)
      for(uint32_t i = 0; i < n; i++)
        for(uint32_t k = 0; k < n; k++)
          Q[i][k] = min(Q[i][k], Q[i][j] + Q[j][k]);
    while(q --> 0)
    {
        uint32_t u, v, w;
        cin >> u >> v >> w; u--; v--;
        bool better = (min(Q[0][u] + Q[v][n-1], Q[0][v] + Q[u][n-1]) + w < Q[0][n-1]);
        if(better)
        {
            for(uint32_t i = 0; i < n; i++)
              for(uint32_t j = 0; j < n; j++)
                Q[i][j] = min(Q[i][j], min(Q[i][u] + Q[v][j], Q[i][v] + Q[u][j]) + w);
        }
        cout << better << "\n";
    }
}
