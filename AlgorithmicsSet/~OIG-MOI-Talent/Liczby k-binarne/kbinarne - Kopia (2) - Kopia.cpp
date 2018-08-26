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
            for(uint32_t b = 0; b < 2; b++)
              for(uint32_t s = 0; s < 2; s++)
                for(uint32_t c = 0; c < 64-i; c++)
                  DP[i][0][0][c] += DP[i+1][b][s][c];
            for(uint32_t b = 0; b < 2; b++)
              for(uint32_t s = 0; s < 2; s++)
                for(uint32_t c = 1; c < 64-i; c++)
                  DP[i][1][0][c] += DP[i+1][b][s][c-1];
            for(uint32_t b = 0; b < 2; b++)
              for(uint32_t c = 1; c < 64-i; c++)
                DP[i][1][1][c] += DP[i+1][b][1][c-1];
        }
        else
        {
            for(uint32_t b = 0; b < 2; b++)
              for(uint32_t c = 0; c < 64-i; c++)
                DP[i][0][0][c] += DP[i+1][b][0][c];
            for(uint32_t b = 0; b < 2; b++)
              for(uint32_t c = 1; c < 64-i; c++)
                DP[i][1][0][c] += DP[i+1][b][0][c-1];
            for(uint32_t b = 0; b < 2; b++)
              for(uint32_t c = 0; c < 64-i; c++)
                DP[i][0][1][c] += DP[i+1][b][1][c];
        }
    }
    cout << DP[0][0][0][k] + DP[0][1][0][k] +
            DP[0][0][1][k] + DP[0][1][1][k];
}
