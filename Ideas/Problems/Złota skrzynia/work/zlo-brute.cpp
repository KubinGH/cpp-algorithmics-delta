#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 128;

uint32_t A[MAX][MAX][MAX];
uint32_t sum_brute(uint32_t x1, uint32_t y1, uint32_t z1,
                   uint32_t x2, uint32_t y2, uint32_t z2)
{
    uint32_t r = 0;
    for(uint32_t z = z1; z <= z2; z++)
        for(uint32_t y = y1; y <= y2; y++)
            for(uint32_t x = x1; x <= x2; x++)
                r += A[z][y][x];
    return r;
}

int main()
{
    uint32_t w, h, d, k;
    cin >> w >> h >> d >> k;
    for(uint32_t z = 0; z < d; z++)
        for(uint32_t y = 0; y < h; y++)
            for(uint32_t x = 0; x < w; x++)
                cin >> A[z][y][x];
    uint32_t r = 0;
    for(uint32_t z = 0; z <= d - k; z++)
        for(uint32_t y = 0; y <= h - k; y++)
            for(uint32_t x = 0; x <= w - k; x++)
                r = max(r, sum_brute(x, y, z, x+k-1, y+k-1, z+k-1));
    cout << r;
}


