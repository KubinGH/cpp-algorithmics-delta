#include <bits/stdc++.h>

using namespace std;

using uint = unsigned;
const uint mod = 998'244'353;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S, T;
    cin >> S >> T;

    const size_t n = S.size(), m = T.size();

    static uint F[1<<12][1<<12];

    for(size_t i = 0; i <= n; i++)
        F[i][i] = 1;

    for(size_t d = 1; d <= n; d++)
      for(size_t i = 0, j = i+d; j <= n; i++, j++)
    {
        const size_t k = j - i - 1;
        if(i >= m or S[k] == T[i])
            F[i][j] += F[i+1][j];
        if(j > m or S[k] == T[j-1])
            F[i][j] += F[i][j-1];
        F[i][j] %= mod;
    }

    uint result = 0;
    for(size_t j = m; j <= n; j++)
        result += F[0][j];

    cout << result % mod << endl;
}
