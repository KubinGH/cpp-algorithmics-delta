#include <bits/stdc++.h>
#define gcd __gcd

using namespace std;

int iabs(int x) { return x<0 ? -x : x; }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;

    uint32_t best = 0, best_count = 0;
    for(uint32_t a = 0; a < n; a++)
    {
        for(uint32_t b = 0; b < m; b++)
        {
            uint32_t curr = 0;

            for(uint32_t x = 0; x < n; x++)
                for(uint32_t y = 0; y < m; y++)
                    if(gcd(iabs(x-a), iabs(y-b)) == 1)
                        curr++;

            if(curr > best)
                best = curr, best_count = 0;
            if(curr == best)
                best_count++;
        }
    }
    cout << best << " " << best_count;
}
