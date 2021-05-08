#include <bits/stdc++.h>

using namespace std;

const size_t MX = 51;
array<array<bool, 128>, 128> A;
array<array<array<uint, 128>, 128>, MX> D, Q;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m; uint mod;
    cin >> n >> m >> mod;

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        A[u][v] = true;
    }

    for(size_t u = 0; u < n; u++)
        D[0][u][u] = 1;
    for(size_t d = 0; d+1 < MX; d++)
        for(size_t u = 0; u < n; u++)
            for(size_t v = 0; v < n; v++)
                for(size_t w = 0; w < n; w++)
                    if(A[v][w])
                        D[d+1][u][w] += D[d][u][v], D[d+1][u][w] %= mod;

    for(size_t u = 0; u < n; u++)
      for(size_t v = 0; v < n; v++)
    {
        array<array<uint, 128>, MX> P = {};
        P[0][v] = 1;

        for(size_t x = 1; x < MX; x++)
          for(size_t u1 : {u, v})
        {
            uint sum = 0;
            for(size_t y = 1; y < x; y++)
                for(size_t w : {u, v})
                    sum += ((uint64_t)D[y][u1][w] * P[x-y][w]) % mod, sum %= mod;
            P[x][u1] = (mod + D[x][u1][v] - sum) % mod;
        }

        for(size_t d = 0; d < MX; d++)
            Q[d][u][v] = P[d][u];
    }

    size_t q;
    cin >> q;

    while(q --> 0)
    {
        size_t u, v, d;
        cin >> u >> v >> d; u--; v--;

        cout << Q[d][u][v] << '\n';
    }
}
