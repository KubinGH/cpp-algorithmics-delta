#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 500000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n;
    cin >> n;
    static array<uint64_t, MAX> A;
    uint64_t maxim = 0;
    for(uint32_t i = 0; i < n; i++)
        cin >> A[i], maxim = max(maxim, A[i]);
    uint64_t lo = maxim, hi = max(n, maxim);
    while(lo < hi)
    {
        uint32_t x = (lo + hi) / 2, c = 0, u = 1;
        for(uint32_t i = 0; i < n and u <= x; i++)
        {
            if(c + A[i] > x)
                u++, c = A[i];
            else
                c += A[i];
        }
        if(u <= x)
            hi = x;
        else
            lo = x + 1;
    }
    cout << lo;
}
