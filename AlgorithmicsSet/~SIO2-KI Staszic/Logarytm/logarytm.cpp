#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t a, c, p;
    while(cin >> a >> c >> p)
    {
        uint64_t x = 1;
        int64_t r = -1;
        for(uint64_t b = 0; b < p - 1; b++)
        {
            if(x == c)
            {
                r = b;
                break;
            }
            x *= a; x %= p;
        }
        cout << r << '\n';
    }
}
