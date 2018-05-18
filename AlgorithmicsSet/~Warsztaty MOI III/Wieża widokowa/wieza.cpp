#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int64_t n;
    cin >> n;
    static int64_t H[MAX+1];
    for(uint32_t i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        H[i+1] = H[i];
        if(c == 'D')
            H[i+1]--;
        else if(c == 'G')
            H[i+1]++;
    }
    for(uint32_t i = 0; i <= n; i++)
        H[i] *= n;
    int64_t lo = 0, hi = n * 3e6;
    while(lo < hi)
    {
        int64_t x = (lo + hi) / 2;
        int64_t a = (H[n] + x) / n;
        bool ok = true;
        for(int64_t i = 0; i <= n and ok; i++)
        {
            if(a*i <= H[i] and not ((i == 0 or i == n) and a*i >= H[i]))
                ok = false;
        }
        if(ok)
            hi = x;
        else
            lo = x + 1;
    }
    cout << (lo + n - 1) / n;
}
