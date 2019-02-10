#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;

    vector<uint64_t> F(n+1);
    F[0] = 1;
    for(uint32_t d = 1; d <= n; d++)
        F[d] = (F[d-1] * d) % MOD;
    vector<vector<uint64_t>> C(n+1, vector<uint64_t>(n+1));
    for(uint32_t i = 0; i <= n; i++)
        C[i][0] = C[i][i] = 1;
    for(uint32_t i = 0; i <= n; i++)
        for(uint32_t j = 1; j < i; j++)
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;

    vector<vector<uint64_t>> G(n, vector<uint64_t>(n+1));
    for(uint32_t i = 0; i < n; i++)
        cin >> G[i][i+1];

    vector<char> op(n-1);
    for(uint32_t i = 0; i < n - 1; i++)
        cin >> op[i];

    for(uint32_t d = 2; d <= n; d++)
    {
        for(uint32_t i = 0, j = d; j <= n; i++, j++)
        {
            for(uint32_t k = i+1; k < j; k++)
            {
                char o = op[k-1];
                uint64_t v;
                if(o == '*')
                    v = G[i][k] * G[k][j];
                else
                {
                    uint64_t a = G[i][k] * F[j-k-1],
                             b = G[k][j] * F[k-i-1];
                    if(o == '+')
                        v = a + b;
                    else if(o == '-')
                        v = MOD*MOD + a - b;
                }
                v = ((v % MOD) * C[d-2][k-i-1]) % MOD;
                G[i][j] += v; G[i][j] %= MOD;
            }
        }
    }
    cout << G[0][n];
}
