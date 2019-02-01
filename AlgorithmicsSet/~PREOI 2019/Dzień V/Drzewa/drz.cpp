#include <bits/stdc++.h>
#define gcd __gcd

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;

    const uint32_t k = max(n, m);
    vector<vector<uint32_t>> limphi(k+1);

    limphi[1] = {1, 2};
    for(uint32_t i = 2; i <= k; i++)
    {
        limphi[i].resize(i+1);
        for(uint32_t j = 1; j <= i; j++)
            limphi[i][j] = limphi[i][j-1] + (gcd(i, j) == 1);
    }

    vector<vector<uint32_t>> X(n+1, vector<uint32_t>(m+1));
    for(uint32_t a = 1; a <= n; a++)
        X[a][0] = 1;
    for(uint32_t b = 1; b <= m; b++)
        X[0][b] = 1;
    for(uint32_t a = 1; a <= n; a++)
        for(uint32_t b = 1; b <= m; b++)
    {
        if(a > b)
            X[a][b] = X[a-1][b] + limphi[a][b];
        else
            X[a][b] = X[a][b-1] + limphi[b][a];
    }

    uint32_t best = 0, best_count = 0;
    for(uint32_t x = 0; x < n; x++)
    {
        for(uint32_t y = 0; y < m; y++)
        {
            uint32_t curr =
                X[x][y] +
                X[x][m-y-1] +
                X[n-x-1][y] +
                X[n-x-1][m-y-1] -
                ((x>0) + (y>0) + (x+1<n) + (y+1<m));
            if(curr > best)
                best = curr, best_count = 0;
            if(curr == best)
                best_count++;
        }
    }
    cout << best << " " << best_count;
}
