#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000000;
const size_t MAX_V = 2e9;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    static array<uint64_t, MAX> W;
    uint64_t s = 0;
    for(uint32_t i = 0; i < n; i++)
        cin >> W[i], s += W[i];
    uint64_t lo = s / k - 1, hi = s + 1;
    while(lo < hi)
    {
        uint64_t maximum_used = (lo + hi) / 2;
        uint64_t current = 0, used_groups = 1, li = 0;
        for(uint32_t i = 0; i < n and used_groups <= k; i++)
        {
            if(W[i] > maximum_used)
            {
                used_groups = -1; break;
            }
            if(current + W[i] <= maximum_used and not (i < n - 1 and W[i] + W[i+1] > maximum_used))
                current += W[i];
            else
            {
                used_groups++;
                current = W[i];
                if(i - li <= 1)
                {
                    used_groups = -1; break;
                }
                li = i;
            }
        }
        if(used_groups > k)
            lo = maximum_used+1;
        else
            hi = maximum_used;
    }
    cout << lo;
}
