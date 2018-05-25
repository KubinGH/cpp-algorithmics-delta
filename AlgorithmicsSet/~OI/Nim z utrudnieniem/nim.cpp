#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 5e5+16, MAX_A = 1<<20, MAX_D = 10;
const uint32_t MOD = 1e9+7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, d;
    cin >> n >> d;
    static uint32_t A[MAX_N], R[2][MAX_D][MAX_A];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i+1];
    sort(A + 1, A + n+1);
    // R[index][removed][number]
    R[0][0][0] = 1;
    uint32_t x = 0;
    for(uint32_t i = 1; i <= n; i++)
    {
        uint32_t a = i%2, b = 1-i%2, c = A[i];
        x ^= c;
        for(uint32_t j = 0; j < d; j++)
        {
            for(uint32_t k = 0; k < min(MAX_A, 2*c); k++)
            {
                R[a][j][k] = (R[b][j][k^c] + R[b][(d+j-1)%d][k]) % MOD;
            }
        }
    }
    cout << (MOD + R[n%2][0][0] - (n%d==0)) % MOD;
}
