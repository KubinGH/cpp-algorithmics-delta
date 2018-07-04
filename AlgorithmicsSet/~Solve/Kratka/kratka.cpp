#include <bits/stdc++.h>

using namespace std;

const uint32_t MAX = 2e5, M = 8;
const uint32_t MASKS[] = {
    0, 1, 2, 4, 5, 8, 9, 10
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static uint64_t A[MAX][4];
    for(uint32_t j = 0; j < 4; j++)
        for(uint32_t i = 0; i < n; i++)
            cin >> A[i][j];
    static uint64_t S[MAX][M];
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t m = 0; m < M; m++)
        {
            for(uint32_t j = 0; j < 4; j++)
                if(MASKS[m] & (1u << j))
                    S[i][m] += A[i][j];
        }
    }
    static uint64_t R[MAX][M];
    for(uint32_t m = 0; m < M; m++)
        R[0][m] = S[0][m];
    for(uint32_t i = 1; i < n; i++)
    {
        for(uint32_t m = 0; m < M; m++)
        {
            for(uint32_t m1 = 0; m1 < M; m1++)
            {
                if((MASKS[m] & MASKS[m1]) == 0)
                    R[i][m] = max(R[i][m], S[i][m] + R[i-1][m1]);
            }
        }
    }
    uint64_t r = 0;
    for(uint32_t m = 0; m < M; m++)
        r = max(r, R[n-1][m]);
    cout << r;
}
