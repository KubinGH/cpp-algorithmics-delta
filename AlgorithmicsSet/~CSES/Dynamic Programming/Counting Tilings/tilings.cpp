#include <bits/stdc++.h>

using namespace std;

const uint64_t mod = 1e9 + 7;

void doplus(uint64_t& a, uint64_t b)
{
    a += b; a %= mod;
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<vector<vector<uint64_t>>> R(m+1, vector<vector<uint64_t>>(n+1, vector<uint64_t>(1 << n)));
    R[0][n][(1<<n)-1] = 1;

    for(size_t i = 0; i < m; i++)
    {
        for(size_t mask = 0; mask < (1u << n); mask++)
            R[i+1][0][mask] = R[i][n][mask];

        for(size_t k = 1; k <= n; k++)
        {
            for(size_t mask = 0; mask < (1u << n); mask++)
            {
                if(mask >> (k-1) & 1)
                    doplus(R[i+1][k][mask & ~(1 << (k-1))], R[i+1][k-1][mask]);
                if(not (mask >> (k-1) & 1))
                    doplus(R[i+1][k][mask | (1 << (k-1))], R[i+1][k-1][mask]);
                if(k >= 2 and (mask >> (k-1) & 1) and (mask >> (k-2) & 1))
                    doplus(R[i+1][k][mask | (1 << (k-1)) | (1 << (k-2))], R[i+1][k-2][mask]);
            }
        }
    }

    cout << R[m][n][(1<<n)-1] << endl;
}
