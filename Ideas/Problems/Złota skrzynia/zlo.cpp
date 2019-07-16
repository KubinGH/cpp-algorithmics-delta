#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 128;

uint32_t A[MAX][MAX][MAX], S[MAX+1][MAX+1][MAX+1];
uint32_t sum(uint32_t x1, uint32_t y1, uint32_t z1,
             uint32_t x2, uint32_t y2, uint32_t z2)
{
    return S[z2+1][y2+1][x2+1] + S[z2+1][y1][x1] + S[z1][y2+1][x1] + S[z1][y1][x2+1] - S[z1][y1][x1]
         - S[z1][y2+1][x2+1] - S[z2+1][y1][x2+1] - S[z2+1][y2+1][x1];
}

int main()
{
    uint32_t w, h, d, k;
    cin >> w >> h >> d >> k;
    for(uint32_t z = 0; z < d; z++)
    {
        for(uint32_t y = 0; y < h; y++)
        {
            for(uint32_t x = 0; x < w; x++)
            {
                cin >> A[z][y][x];
                S[z+1][y+1][x+1] = S[z+1][y+1][x] + S[z+1][y][x+1]
                    + S[z][y+1][x+1] + A[z][y][x] + S[z][y][x]
                    - S[z+1][y][x] - S[z][y+1][x] - S[z][y][x+1];
            }
        }
    }
    uint32_t r = 0;
    for(uint32_t z = 0; z <= d - k; z++)
        for(uint32_t y = 0; y <= h - k; y++)
            for(uint32_t x = 0; x <= w - k; x++)
                r = max(r, sum(x, y, z, x+k-1, y+k-1, z+k-1));
    cout << r;
}


