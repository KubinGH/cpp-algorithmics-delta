#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t x, y, dx, dy;
    cin >> x >> y >> dx >> dy;
    uint32_t i = 0;
    for(; i < x + y; i++)
    {
        if(x >= y)
            break;
        x += dx;
        y -= dy;
    }
    cout << i;
}
