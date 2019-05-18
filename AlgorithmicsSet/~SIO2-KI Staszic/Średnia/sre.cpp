#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n + 1));
    for(size_t i = 0; i < n; i++)
        cin >> A[i][i+1];

    for(size_t d = 2; d <= n; d++)
      for(size_t i = 0, j = i+d; j <= n; i++, j++)
        for(size_t p = i+1; p < j; p++)
          A[i][j] = max(A[i][j], (A[i][p] + A[p][j]) / 2);

    cout << fixed << setprecision(7);
    cout << A[0][n];
}
