#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 21;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n; uint64_t m;
    cin >> n >> m;
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i];
    uint32_t lo = 1, hi = n+1;
    while(lo < hi)
    {
        uint32_t p = (lo + hi) / 2;
        static uint64_t DP[MAX];
        DP[p] = 0; DP[p+1] = 0;
        for(uint32_t i = p; i --> 0; )
        {
            if(A[i] == 0) DP[i] = DP[i+1];
            if(A[i] == 1) DP[i] = 2*DP[i+1] + 1;
            if(A[i] == 2) DP[i] = DP[i+1] + DP[i+2] + 1;
            if(DP[i] >= m)
            {
                DP[0] = DP[i];
                break;
            }
        }
        if(DP[0] >= m)
            hi = p;
        else
            lo = p + 1;
    }
    if(lo <= n)
        cout << lo;
    else
        cout << "NIE";
}
