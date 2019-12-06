#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;
const uint64_t BASE = 1e9, MOD = (1LLU << 61) - 1;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, p;
    cin >> n >> m >> p;
    static array<array<uint32_t, MAX>, MAX> A;
    for(uint32_t i = 0; i < n; i++)
    {
        for(uint32_t j = 0; j < m; j++)
            cin >> A[i][j], A[i][j]--;
        sort(A[i].begin(), A[i].begin() + m);
    }
    static array<uint32_t, MAX> K;
    static array<uint64_t, MAX> H;
    static array<array<uint32_t, 2*MAX>, MAX> V;
    map<uint64_t, uint32_t> C;
    uint32_t result = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        V[i][0] = (A[i][0] + p - A[i][m-1]) % p;
        for(uint32_t j = 1; j < m; j++)
            V[i][j] = A[i][j] - A[i][j-1];
        for(uint32_t j = m; j < 2*m; j++)
            V[i][j] = V[i][j-m];
        static array<int32_t, MAX> F;
        F.fill(-1);
        uint32_t& k = K[i];
        for(uint32_t j = 1; j < m; j++)
        {
            int32_t i = F[j-k-1];
            while(i != -1 and V[i][j] != V[i][k+i+1])
            {
                if(V[i][j] < V[i][k+i+1])
                    k = j-i-1;
                i = F[i];
            }
            if(V[i][j] != V[i][k+i+1])
            {
                if(V[i][j] < V[i][k])
                    k = j;
                F[j-k] = -1;
            }
            else
                F[j-k] = i+1;
        }
        H[i] = V[i][K[i]];
        for(uint32_t j = 1; j < m; j++)
        {
            uint64_t c = V[i][j+K[i]];
            H[i] = (H[i] * BASE + c) % MOD;
        }
        result += C[H[i]];
        C[H[i]]++;
    }
    cout << result;
}
