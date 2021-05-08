#include <bits/stdc++.h>

using namespace std;

const uint64_t mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<uint64_t>> R(n+1, vector<uint64_t>(m+2));

    for(size_t i = 1; i <= n; i++)
    {
        if(i > 1) for(size_t k = 1; k <= m; k++)
            R[i][k] = (R[i-1][k-1] + R[i-1][k]  + R[i-1][k+1]) % mod;
        else
            fill(R[1].begin() + 1, R[1].begin() + (m+1), 1);
        size_t k0;
        cin >> k0;
        if(k0)
        {
            auto x = R[i][k0];
            fill(R[i].begin(), R[i].end(), 0);
            R[i][k0] = x;
        }
    }

    cout << accumulate(R.back().begin(), R.back().end(), 0ul) % mod << endl;
}
