#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e4, MAX_M = 20;

int main()
{
    uint32_t n, m, k;
    cin >> n >> m >> k;
    static uint64_t A[MAX], S[MAX+1];
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        S[i+1] = S[i] + A[i];
    }
    static uint64_t R[MAX+1][MAX_M+1];
    uint64_t r = 0;
    for(uint32_t i = 1; i <= n; i++)
    {
        for(uint32_t mi = 0; mi <= m; mi++)
        {
            for(uint32_t mip = 0; mip <= mi; mip++)
                R[i][mi] = R[i-1][mip];
            for(uint32_t ki = k; ki <= mi; ki++)
            {
                if(i < ki or mi < ki)
                    continue;
                R[i][mi] = max(R[i][mi], R[i-ki][mi-ki] + (S[i] - S[i-ki]));
            }
            r = max(r, R[i][mi]);
        }
    }
    cout << r;
}
