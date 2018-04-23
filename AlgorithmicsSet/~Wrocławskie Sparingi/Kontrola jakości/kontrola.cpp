#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m, k;
    cin >> n >> m >> k;
    static array<uint32_t, MAX> A;
    static array<uint32_t, MAX+1> S;
    for(uint32_t i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        A[i] = c == '-';
        S[i+1] = S[i] + A[i];
    }
    uint32_t lo = 0, hi = n / m + 1;
    while(lo < hi)
    {
        uint32_t x = (lo + hi) / 2;
        uint32_t ti = 0, u = 0;
        for(uint32_t tj = 1; tj <= n; tj++)
        {
            if(S[tj] - S[ti] > k)
                ti++;
            if(tj - ti >= x)
            {
                u++;
                ti = tj;
            }
        }
        if(u >= m)
            lo = x + 1;
        else
            hi = x;
    }
    cout << lo - 1;
}
