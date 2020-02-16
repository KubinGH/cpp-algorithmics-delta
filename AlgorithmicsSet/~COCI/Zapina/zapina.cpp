#include <iostream>

using namespace std;

const uint Mod = 1e9 + 7;

int main()
{
    size_t n;
    cin >> n;

    static uint B[512][512];
    B[0][0] = 1;
    for(size_t m = 1; m <= n; m++)
        for(size_t k = 0; k <= m; k++)
            B[m][k] = k ? (B[m-1][k] + B[m-1][k-1]) % Mod : 1;

    static uint C[512][512][2];
    C[0][0][0] = 1;

    for(size_t i = 1; i <= n; i++)
    {
        for(size_t t = 0; t <= n; t++)
        {
            for(size_t h = 0; h <= t; h++)
            {
                C[i][t][h == i] += (uint64_t) C[i-1][t-h][0] * B[t][h] % Mod;
                C[i][t][1] += (uint64_t) C[i-1][t-h][1] * B[t][h] % Mod;
                C[i][t][0] %= Mod; C[i][t][1] %= Mod;
            }
        }
    }

    cout << C[n][n][1] << endl;
}
