#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#endif // not

using namespace std;

const size_t MAX = 100;

const uint8_t TILE_EMPTY = 0, TILE_HOLE = 1, TILE_TELEPORT = 2;


int main()
{
    uint16_t hh, wh, th; uint32_t k = 0;
    cin >> hh >> wh >> k >> th;
    uint8_t h = hh, w = wh, t = th;
    static array<pair<uint8_t, uint8_t>, MAX> M;
    for(uint8_t i = 0; i < t; i++)
    {
        uint16_t mx, my;
        cin >> mx >> my;
        M[i].first = mx; M[i].second = my;
    }
    static array<array<uint8_t, MAX>, MAX> T;
    for(uint8_t y = 0; y < h; y++)
    {
        for(uint8_t x = 0; x < w; x++)
        {
            char c = getchar();
            if(c == '.')
                T[y][x] = TILE_EMPTY;
            else if(c == 'D')
                T[y][x] = TILE_HOLE;
            else if(c == 'H')
                T[y][x] = TILE_TELEPORT;
        }
        getchar();
    }
    while(true)
    {
        uint16_t sxh, syh;
        cin >> sxh;
        if(sxh == 0) break;
        cin >> syh;
        uint8_t sx = sxh, sy = syh; sx--; sy--;
        queue<tuple<pair<uint8_t, uint8_t>, uint32_t> > Q;
    }
}
