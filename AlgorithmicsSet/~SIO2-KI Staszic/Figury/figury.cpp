#include <bits/stdc++.h>
#define ADDIFNEW(x, y) { if(not V[y][x]) Q.emplace((x), (y)), V[y][x] = true; }
#ifdef __linux__
#define getchar getchar_unlocked
#endif // __linux__

using namespace std;

const size_t MAX = 2000;

int main()
{
    uint16_t h, w;
    cin >> h >> w;
    getchar();
    static array<array<bool, MAX>, MAX> A;
    for(uint16_t y = 0; y < h; y++)
    {
        for(uint16_t x = 0; x < w; x++)
            A[y][x] = (getchar() == 'X');
        getchar();
    }
    uint16_t sy, sx;
    cin >> sy >> sx; sy--; sx--;
    queue<pair<uint16_t, uint16_t> > Q;
    Q.emplace(sx, sy);
    static array<array<bool, MAX>, MAX> V;
    V[sy][sx] = true;
    uint32_t r = 0;
    while(not Q.empty())
    {
        uint16_t x = Q.front().first, y = Q.front().second; Q.pop();
        if(x > 0 and A[y][x-1])
            ADDIFNEW(x - 1, y)
        else
            r++;
        if(x < w - 1 and A[y][x+1])
            ADDIFNEW(x + 1, y)
        else
            r++;
        if(y > 0 and A[y-1][x])
            ADDIFNEW(x, y - 1)
        else
            r++;
        if(y < h - 1 and A[y+1][x])
            ADDIFNEW(x, y + 1)
        else
            r++;
    }
    cout << r;
}
