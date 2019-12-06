#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;

    vector<int> A(n);
    for(auto& a : A) cin >> a;

    vector<vector<int>> Q(n + 1, vector<int>(n + 1));

    for(size_t d = 1; d <= n; d++)
    {
        for(size_t i = 0, j = i+d; j <= n; i++, j++)
        {
            Q[i][j] = (d > 1) + Q[i+1][j];
            for(size_t k = i+1; k < j; k++)
                if(A[i] == A[k])
                    Q[i][j] = min(Q[i][j], (i+1 < k) + Q[i+1][k] + Q[k][j]);
        }
    }

    cout << Q[0][n] + 1;
}
