#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        int64_t sx, sy, r, x, y;
        cin >> sx >> sy >> r >> x >> y;
        int64_t d = (x-sx)*(x-sx) + (y-sy)*(y-sy);
        if(d < r*r)
            cout << "-1\n";
        else if(d == r*r)
            cout << "0\n";
        else
            cout << "1\n";
    }
}
