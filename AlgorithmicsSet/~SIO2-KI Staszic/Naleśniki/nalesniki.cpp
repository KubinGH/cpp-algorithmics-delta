#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2001;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t n, m;
    cin >> n >> m;
    static array<int64_t, MAX> A, B, SA, SB;
    for(uint16_t i = 0; i < n; i++)
        cin >> A[i], SA[i+1] += SA[i] + A[i];
    for(uint16_t i = 0; i < m; i++)
        cin >> B[i], SB[i+1] += SB[i] + B[i];
    static array<array<int64_t, MAX+1>, MAX+1> R;
    for(uint16_t i = 0; i <= n; i++)
    {
        for(uint16_t j = 0; j <= m; j++)
        {
            if(i == 0 and j == 0)
                R[i][j] = 0;
            else if(j == 0)
                R[i][j] = SA[i] - R[i-1][j];
            else if(i == 0)
                R[i][j] = SB[j] - R[i][j-1];
            else
                R[i][j] = SA[i] + SB[j] - min(R[i-1][j], R[i][j-1]);
        }
    }
    cout << R[n][m] << endl;
}
