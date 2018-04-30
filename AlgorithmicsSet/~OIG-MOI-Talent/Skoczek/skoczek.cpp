#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 2e5+2;

typedef unsigned int uint32_t;

char R[MAX]; uint32_t i = 0, x = 1, y = 1;

void x1y0() { R[i++] = '3'; R[i++] = '6'; R[i++] = '1'; x++; }
void x0y1() { R[i++] = '4'; R[i++] = '1'; R[i++] = '6'; y++; }
void x4y0() { R[i++] = '3'; R[i++] = '2'; x += 4; }
void x0y4() { R[i++] = '4'; R[i++] = '5'; y += 4; }

int main()
{
    uint32_t h, w;
    scanf("%u %u", &h, &w);
    uint32_t tx = w - 1, ty = h - 2;
    while(x < tx)
    {
        if(tx - x >= 4)
            x4y0();
        else
            x1y0();
    }
    while(y < ty)
    {
        if(ty - y >= 4)
            x0y4();
        else
            x0y1();
    }
    R[i++] = '4';
    assert(x == tx and y == ty);
    printf("%u\n%s", i, R);
}
