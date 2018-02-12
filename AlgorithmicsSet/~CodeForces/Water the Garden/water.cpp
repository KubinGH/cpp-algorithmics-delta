#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t n, k;
        cin >> n >> k;
        uint32_t c;
        cin >> c;
        if(k == 1)
        {
            cout << max(c, n - c + 1) << '\n';
            continue;
        }
        uint32_t r = c, b = c;
        for(uint32_t i = 1; i < k; i++)
        {
            cin >> c;
            r = max(r, (c - b) / 2 + 1);
            b = c;
        }
        r = max(r, n - c + 1);
        cout << r << '\n';
    }
}
