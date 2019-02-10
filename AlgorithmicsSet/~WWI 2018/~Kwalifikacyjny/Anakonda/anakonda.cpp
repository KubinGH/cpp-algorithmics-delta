#include <bits/stdc++.h>
#define sum(_i, _j) (S[_j+1] - S[_i])

using namespace std;

const size_t MAX = 1e4;
const uint64_t MOD = 1e9+7;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, d;
    cin >> n >> d;
    static uint64_t A[MAX], S[MAX+1], R[2][MAX+1];
    for(uint32_t i = 0; i < n; i++)
    {
        cin >> A[i];
        S[i+1] = S[i] + A[i];
    }
    uint64_t maxd = 0;
    for(uint32_t i = 0, j = 1; j <= n; j++)
    {
        while(i < j and sum(i, j-1) > d)
            i++;
        maxd = max(sum(i, j-1), maxd);
    }
    cout << maxd << " ";
    R[0][1] = 1;
    for(uint32_t j = 2; j <= n and sum(0, j-1) <= d; j++)
        R[0][j] = 1;
    for(uint32_t i = 1; i < n; i++)
    {
        uint32_t iprev = !(i%2), icurr = i%2;
        uint32_t j = 0;
        for(; j < i+1; j++)
            R[icurr][j] = 0;
        for(; j <= n and sum(i, j-1) <= d; j++)
            R[icurr][j] = (R[icurr][j-1] + R[iprev][j] + R[iprev][j-1]) % MOD;
        for(; j <= n; j++)
            R[icurr][j] = 0;
    }
    cout << R[!(n%2)][n];
}
