#include <bits/stdc++.h>

using namespace std;

int main()
{
    size_t n;
    cin >> n;
    int minx = INT_MAX, maxx = INT_MIN, miny = INT_MAX, maxy = INT_MIN;
    for(size_t i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        minx = min(minx, x);
        maxx = max(maxx, x);
        miny = min(miny, y);
        maxy = max(maxy, y);
    }

    if(minx == maxx and miny == maxy)
        cout << 1;
    else if(miny == maxy)
        cout << maxx - minx;
    else if(minx == maxx)
        cout << maxy - miny;
    else
        cout << (maxy - miny) * (maxx - minx);
}
