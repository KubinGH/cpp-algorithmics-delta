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
        cin >> B[i]; // i or i + 1

    vector<array<uint64_t, 2>> W(n+1);
    W[0] = {1, 0};
    for(size_t i = 1; i <= n; i++)
    {
        W[i][0] = (A[i] + B[i-1]) * (W[i-1][0] + W[i-1][1]) - W[i-1][1];
        W[i][1] = B[i] * (W[i-1][0] + W[i-1][1]);
    }

    cout << W[n][0] + W[n][1];
}
