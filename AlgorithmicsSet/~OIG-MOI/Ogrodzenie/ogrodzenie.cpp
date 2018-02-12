#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef int int32_t;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    int32_t startx, starty, x1, y1, x2, y2;
    scanf("%u %u", &startx, &starty);
    x1 = startx; y1 = starty;
    printf("%u %u\n", x1, y1);
    for(uint32_t i = 0; i < n; i++)
    {
        if(i < n - 1) scanf("%u %u", &x2, &y2);
        else { x2 = startx; y2 = starty; }
        int32_t dx = abs(x2 - x1), dy = abs(y2 - y1);
        int32_t xsign = x2 < x1 ? -1 : 1, ysign = y2 < y1 ? -1 : 1;
        int32_t g = __gcd(dx, dy);
        int32_t sx = dx / g * xsign, sy = dy / g * ysign;
        int32_t px = x1, py = y1;
        while(px != x2 or py != y2)
        {
            px += sx; py += sy;
            if(i < n - 1 or px != x2 or py != y2)
                printf("%u %u\n", px, py);
        }
        x1 = x2; y1 = y2;
    }
}
