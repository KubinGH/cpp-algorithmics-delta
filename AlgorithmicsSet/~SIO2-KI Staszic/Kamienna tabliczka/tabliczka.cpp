#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

void find_string(char (&A)[MAX][MAX+1], uint16_t x, uint16_t y,
                 uint16_t dx, uint16_t dy, uint16_t w, uint16_t h,
                 string key, uint16_t (&R)[MAX][MAX])
{
    uint32_t i = 0;
    for(; x < w and y < h; x += dx, y += dy)
    {
        if(A[y][x] == key[i])
            i++;
        else
        {
            i = 0;
            if(A[y][x] == key[i])
                i++;
        }
        if(i == key.size())
        {
            uint16_t ix = x, iy = y;
            while(i--)
            {
                R[iy][ix]++;
                ix -= dx; iy -= dy;
            }
            i = 0;
            if(A[y][x] == key[i])
                i++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t h, w;
    cin >> h >> w;
    static char A[MAX][MAX+1];
    static uint16_t R[MAX][MAX];
    for(uint16_t y = 0; y < h; y++)
        cin >> A[y];
    uint16_t k; string key;
    cin >> k >> key;
    for(uint16_t y = 0; y < h; y++)
        find_string(A, 0, y, 1, 0, w, h, key, R);
    for(uint16_t x = 0; x < w; x++)
        find_string(A, x, 0, 0, 1, w, h, key, R);
    uint32_t r = 0;
    for(uint16_t y = 0; y < h; y++)
    {
        for(uint16_t x = 0; x < w; x++)
        {
            if(R[y][x] >= 2)
                r++;
        }
    }
    cout << r;
}
