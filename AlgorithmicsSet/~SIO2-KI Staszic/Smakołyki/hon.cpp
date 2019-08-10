#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    vector<uint64_t> A(n+1), B(n+1);
    for(size_t i = 1; i <= n; i++)
        cin >> A[i];
    for(size_t i = 1; i < n; i++)
        cin >> B[i];

    vector<array<uint64_t, 2>> W(n+1);
    W[0] = {1, 1};
    for(size_t i = 1; i <= n; i++)
    {
        W[i][0] = (A[i] + B[i]) * W[i-1][0];
        W[i][0] += B[i-1] * W[i-1][1];

        if(B[i])
        {
            W[i][1] = (A[i] + B[i] - 1) * W[i-1][0];
            W[i][1] += B[i-1] * W[i-1][1];
        }

        W[i][0] %= MOD;
        W[i][1] %= MOD;
    }

    cout << W[n][0];
}
