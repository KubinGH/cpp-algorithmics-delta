#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int64_t> A(n);
    for(auto& a : A)
        cin >> a;

    vector<int64_t> S(n+1);
    partial_sum(A.begin(), A.end(), S.begin() + 1);

    vector<vector<int64_t>> W(n+1, vector<int64_t>(n+1));
    for(size_t d = 1; d <= n; d++)
        for(size_t i = 0, j = d; j <= n; i++, j++)
            W[i][j] = max(
                (S[j]-S[i+1] - W[i+1][j]) + A[i],
                (S[j-1]-S[i] - W[i][j-1]) + A[j-1]
            );

    cout << W[0][n] << endl;
}
