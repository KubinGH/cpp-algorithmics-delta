#include <bits/stdc++.h>
#ifndef XHOVA
#define double long double
#endif // XHOVA

using namespace std;

const size_t MAX = 3042;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k; k--;
    cout << fixed << setprecision(13);
    static uint64_t W[MAX], S[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> W[i];
    partial_sum(W, W + n, S + 1);
    static double Q[MAX][MAX];
    for(uint32_t i = 0; i < n; i++)
        Q[i][i+1] = 0;
    Q[k][k+1] = 1;
    for(uint32_t d = 2; d <= n; d++)
    {
        for(uint32_t i = 0; i <= n - d; i++)
        {
            uint32_t j = i + d;
            for(uint32_t m = i+1; m <= j-1; m++)
            {
                uint64_t a = S[m] - S[i], b = S[j] - S[m];
                if(a > b)
                    Q[i][j] += Q[i][m];
                else if(a < b)
                    Q[i][j] += Q[m][j];
            }
            Q[i][j] /= d - 1;
        }
    }
    cout << Q[0][n];
}
