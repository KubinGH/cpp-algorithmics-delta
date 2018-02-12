#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t w, h, cw, ch;
    cin >> w >> h >> cw >> ch;
    static array<array<uint16_t, MAX>, MAX> A, C;
    for(uint16_t y = 0; y < h; y++)
        for(uint16_t x = 0; x < w; x++)
            cin >> A[y][x];
    for(uint16_t y = 0; y < ch; y++)
        for(uint16_t x = 0; x < cw; x++)
            cin >> C[y][x];
    uint32_t r = 0;
    for(uint16_t cy = 0; cy < h-ch+1; cy++)
    {
        for(uint16_t cx = 0; cx < w-ch+1; cx++)
        {
            for(uint16_t y = cy; y < cy+ch; y++)
            {
                for(uint16_t x = cx; x < cx+cw; x++)
                {
                    if(A[y][x] != C[y-cy][x-cx])
                        goto next;
                }
            }
            r++;
        next:;
        }
    }
    cout << r << endl;
}
