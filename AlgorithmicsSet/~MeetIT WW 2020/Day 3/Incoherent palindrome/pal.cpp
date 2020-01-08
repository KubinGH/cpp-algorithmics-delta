#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    string S;
    cin >> S;

    const size_t n = S.size();

    vector<vector<int>> Q(n+1, vector<int>(n+1, 0));
    for(size_t i = 0; i+1 <= n; i++)
        Q[i][i+1] = 1;

    for(size_t d = 2; d <= n; d++)
        for(size_t i = 0, j = i+d; j <= n; i++, j++)
            Q[i][j] = max({
                Q[i+1][j-1] + 2*(S[i] == S[j-1]),
                Q[i+1][j], Q[i][j-1]
            });

    cout << Q[0][n];
}
