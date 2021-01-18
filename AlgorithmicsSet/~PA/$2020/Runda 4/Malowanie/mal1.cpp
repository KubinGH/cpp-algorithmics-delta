#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m; uint p;
    cin >> n >> m >> p;

    vector<vector<uint>> A(m, vector<uint>(m, 1));
    for(size_t t = 1; t < n; t++)
    {
        vector<uint> L(m+1);
        for(size_t k = 0; k < m; k++)
        {
            L[k+1] = L[k];
            for(size_t i = 0; i <= k; i++)
                L[k+1] += A[i][k], L[k+1] %= p, A[i][k] = 0;
        }

        for(size_t i = 0; i < m; i++)
            for(size_t j = i; j < m; j++)
                A[i][j] = (2*p + L[m] - L[i] - L[m-j-1]) % p;
    }

    uint result = 0;
    for(size_t i = 0; i < m; i++)
        for(size_t j = i; j < m; j++)
            result += A[i][j], result %= p;

    cout << result;

}
