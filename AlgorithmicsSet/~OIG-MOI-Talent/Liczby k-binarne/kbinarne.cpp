#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1234567;

int main()
{
    uint64_t n, k;
    cin >> n >> k;
    bitset<64> A(n);
    // DP[i][digit][strong][count1]
    static uint64_t DP[64][2][2][64], S[64][2][2][64];
    fill(&DP[0][0][0][0], &DP[64][0][0][0], 0);
    fill(&S[0][0][0][0], &S[64][0][0][0], 0);
    DP[60][0][1][0] = 1;
    for(uint32_t i = 60; i --> 0; )
    {
        uint64_t P = 1LLU << uint64_t(i); P %= MOD;
        if(A[i])
        {
            // digit = 0
              // strong = 0
              for(uint32_t c = 0; c <= k; c++)
                DP[i][0][0][c] = (DP[i+1][0][0][c] + DP[i+1][1][0][c]
                                + DP[i+1][0][1][c] + DP[i+1][1][1][c]) % MOD;
              for(uint32_t c = 0; c <= k; c++)
                S[i][0][0][c] = (S[i+1][0][0][c] + S[i+1][1][0][c]
                               + S[i+1][0][1][c] + S[i+1][1][1][c]) % MOD;
            // digit = 1
              // strong = 0
              for(uint32_t c = 1; c <= k; c++)
                DP[i][1][0][c] = (DP[i+1][0][0][c-1] + DP[i+1][1][0][c-1]) % MOD;
              for(uint32_t c = 1; c <= k; c++)
                S[i][1][0][c] = (S[i+1][0][0][c-1] + S[i+1][1][0][c-1]
                               + DP[i][1][0][c] * P) % MOD;
              // strong = 1
              for(uint32_t c = 1; c <= k; c++)
                DP[i][1][1][c] = (DP[i+1][0][1][c-1] + DP[i+1][1][1][c-1]) % MOD;
              for(uint32_t c = 1; c <= k; c++)
                S[i][1][1][c] = (S[i+1][0][1][c-1] + S[i+1][1][1][c-1]
                               + DP[i][1][1][c] * P) % MOD;
        }
        else
        {
            // digit = 0
              // strong = 0
              for(uint32_t c = 0; c <= k; c++)
                DP[i][0][0][c] = (DP[i+1][0][0][c] + DP[i+1][1][0][c]) % MOD;
              for(uint32_t c = 0; c <= k; c++)
                S[i][0][0][c] = (S[i+1][0][0][c] + S[i+1][1][0][c]) % MOD;
              // strong = 1
              for(uint32_t c = 0; c <= k; c++)
                DP[i][0][1][c] = (DP[i+1][0][1][c] + DP[i+1][1][1][c]) % MOD;
              for(uint32_t c = 0; c <= k; c++)
                S[i][0][1][c] = (S[i+1][0][1][c] + S[i+1][1][1][c]) % MOD;
            // digit = 1
              // strong = 0
              for(uint32_t c = 1; c <= k; c++)
                DP[i][1][0][c] = (DP[i+1][0][0][c-1] + DP[i+1][1][0][c-1]) % MOD;
              for(uint32_t c = 1; c <= k; c++)
                S[i][1][0][c] = (S[i+1][0][0][c-1] + S[i+1][1][0][c-1]
                               + DP[i][1][0][c] * P) % MOD;
        }
    }
    cout << (S[0][0][0][k] + S[0][1][0][k]) % MOD;
}
