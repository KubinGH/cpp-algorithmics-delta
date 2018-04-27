#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t t;
    cin >> t;
    for(uint32_t ti = 0; ti < t; ti++)
    {
        double x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        if((y2 - y1) / (x2 - x1) == (y4 - y3) / (x4 - x3) and
           (y1 - y4) / (x1 - x4) == (y3 - y2) / (x3 - x2))
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
}
