#include <bits/stdc++.h>

using namespace std;

const size_t MAX_N = 1 << 10, MAX_A = 1 << 7;

uint16_t min_u16(uint16_t a, uint16_t b) { return a<b ? a : b; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    vector<uint32_t> A(n), S(n+1);
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    partial_sum(A.begin(), A.end(), S.begin()+1);
    if(S[n]%2 == 1) { cout << "WOJNA"; return 0; }
    uint16_t target = S[n] / 2;
    vector<vector<array<uint16_t, 2>>>
        W(n+1, vector<array<uint16_t, 2>>(target+1, {(uint16_t)n, (uint16_t)n}));
    W[0][0][1] = 0;
    for(uint32_t i = 1; i <= n; i++)
    {
        for(uint32_t x = 0; x < A[i-1]; x++)
            W[i][x][0] = min_u16(W[i-1][x][1] + 1, W[i-1][x][0]);
        for(uint32_t x = A[i-1]; x <= target; x++)
        {
            W[i][x][1] = min_u16(W[i-1][x-A[i-1]][1], W[i-1][x-A[i-1]][0] + 1);
            W[i][x][0] = min_u16(W[i-1][x][1] + 1, W[i-1][x][0]);
        }
    }
    uint16_t r = min_u16(W[n][target][0], W[n][target][1]);
    if(r < n)
        cout << r;
    else
        cout << "WOJNA";
}
