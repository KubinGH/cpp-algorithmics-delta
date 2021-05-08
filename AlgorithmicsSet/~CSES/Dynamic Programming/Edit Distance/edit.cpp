#include <bits/stdc++.h>

using namespace std;

const int oo = INT_MAX-0xD;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S, Z;
    cin >> S >> Z;

    const size_t n = S.size(), m = Z.size();

    vector<vector<int>> E(n+1, vector<int>(m+1, +oo));
    E[0][0] = 0;
    for(size_t a = 0; a <= n; a++)
      for(size_t b = 0; b <= m; b++)
    {
        if(a<n) E[a+1][b] = min(E[a+1][b], E[a][b] + 1);
        if(b<m) E[a][b+1] = min(E[a][b+1], E[a][b] + 1);
        if(a<n&&b<m) E[a+1][b+1] = min(E[a+1][b+1], E[a][b] + (S[a] != Z[b]));
    }

    cout << E[n][m] << endl;
}
