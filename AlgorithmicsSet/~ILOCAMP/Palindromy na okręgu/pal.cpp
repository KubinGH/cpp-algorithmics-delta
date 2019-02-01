#include <bits/stdc++.h>

using namespace std;

const size_t N = 1 << 12;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    string S;
    cin >> S;
    S += S;
    static uint32_t Q[N][N];
    for(uint32_t i = 0; i+1 < 2*n; i++)
        Q[i][i+1] = (S[i] != S[i+1]);
    for(uint32_t d = 3; d <= n; d++)
    {
        for(uint32_t i = 0; i+d <= 2*n; i++)
        {
            uint32_t j = i+d-1;
            Q[i][j] = min(Q[i][j-1], Q[i+1][j]) + 1;
            if(S[i] == S[j])
                Q[i][j] = min(Q[i][j], Q[i+1][j-1]);
        }
    }
    uint32_t r = -1u;
    for(uint32_t i = 0; i < n; i++)
        r = min(r, Q[i][i+n-1]);
    cout << r;
}
