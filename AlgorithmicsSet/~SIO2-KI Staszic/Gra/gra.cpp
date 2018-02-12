#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static array<uint32_t, MAX+1> A, S;
    uint16_t n;
    cin >> n;
    for(uint16_t i = 0; i < n; i++)
    {
        cin >> A[i];
        if(i > 0) S[i + 1] = S[i];
        S[i + 1] += A[i];
    }
    if(n == 1)
    {
        cout << A[0] << " " << 0 << endl;
        return 0;
    }
    static array<array<uint32_t, MAX>, MAX> X;
    for(uint16_t i = 0; i < n - 1; i++)
        X[i][i+1] = max(A[i], A[i + 1]);
    for(uint16_t d = 2; d < n; d++)
        for(uint16_t i = 0; i < n - d; i++)
            X[i][i+d] = S[i+d+1] - S[i] - min(X[i+1][i+d], X[i][i+d-1]);
    cout << X[0][n-1] << " " << S[n] - X[0][n-1];
}
