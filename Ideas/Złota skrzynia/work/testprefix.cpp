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
    cin >> w >> h >> d;
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
    cout << endl;
    for(uint32_t z = 0; z <= d; z++)
    {
        for(uint32_t y = 0; y <= h; y++)
        {
            for(uint32_t x = 0; x <= w; x++)
                cout << S[z][y][x] << " ";
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
    for(k = 1; k <= min(d, min(w, h)); k++)
    {
        for(uint32_t z = 0; z <= d - k; z++)
        {
            for(uint32_t y = 0; y <= h - k; y++)
            {
                for(uint32_t x = 0; x <= w - k; x++)
                {
                    uint32_t a = sum(x, y, z, x+k-1, y+k-1, z+k-1),
                             b = sum_brute(x, y, z, x+k-1, y+k-1, z+k-1);
                    cout << a << "/" << b << " ";
                    assert(a == b);
                }
                cout << endl;
            }
            cout << endl;
        }
    }
}


