#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    if(n == 1) { cout << 0; return 0; }
    vector<uint32_t> A(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    vector<vector<uint32_t>> H(n, vector<uint32_t>(n+1));
    for(uint32_t i = 0; i < n; i++)
        H[i][i+1] = 1;
    for(uint32_t d = 2; d <= n; d++)
    {
        for(uint32_t i = 0; i+d <= n; i++)
        {
            uint32_t j = i+d;
            H[i][j] = -1u;
            for(uint32_t m = i+1; m < j; m++)
                H[i][j] = min(H[i][j], max(H[i][m], H[m][j]) + (A[m-1] > A[m]));
            //cout << i << ".." << j << ": " << H[i][j] << endl;
        }
    }
    cout << H[0][n]+1;
}
