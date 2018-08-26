#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n, k;
    cin >> n >> k;
    bitset<64> A(n);
    // DP[i][digit][strong][count1]
    static uint32_t DP[64][2][2][64];
    DP[63][A[63]][1][A[63]] = 1;
    if(A[63])
        DP[63][0][0][0] = 1;
    for(uint32_t i = 63; i --> 0; )
    {
        if(A[i])
        {
            // digit = 0
              // strong = 0
              for(uint32_t c = 0; c <= k; c++)
                DP[i][0][0][c] = DP[i+1][0][0][c] + DP[i+1][1][0][c]
                               + DP[i+1][0][1][c] + DP[i+1][1][1][c];
            // digit = 1
              // strong = 0
              for(uint32_t c = 1; c <= k; c++)
                DP[i][1][0][c] = DP[i+1][0][0][c-1] + DP[i+1][1][0][c-1]
                               + DP[i+1][0][1][c-1] + DP[i+1][1][1][c-1];
              // strong = 1
              for(uint32_t c = 1; c <= k; c++)
                DP[i][1][1][c] = DP[i+1][0][1][c-1] + DP[i+1][1][1][c-1];
        }
        else
        {
            // digit = 0
              // strong = 0
              for(uint32_t c = 0; c <= k; c++)
                DP[i][0][0][c] = DP[i+1][0][0][c] + DP[i+1][1][0][c];
              // strong = 1
              for(uint32_t c = 0; c <= k; c++)
                DP[i][0][1][c] = DP[i+1][0][1][c] + DP[i+1][1][1][c];
            // digit = 1
              // strong = 0
              for(uint32_t c = 1; c <= k; c++)
                DP[i][1][0][c] = DP[i+1][0][0][c-1] + DP[i+1][1][0][c-1];
        }
        cout << DP[i][0][0][k] + DP[i][1][0][k] +
                DP[i][0][1][k] + DP[i][1][1][k] << endl;
    }
    cout << DP[0][0][0][k] + DP[0][1][0][k] +
            DP[0][0][1][k] + DP[0][1][1][k];
}
