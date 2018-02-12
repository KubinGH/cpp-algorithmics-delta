#include <bits/stdc++.h>
#define VALID(x, y) (0 <= (x) and (x) < w and 0 <= (y) and (y) < h)
#define CONSIDER(px, py) \
            if(VALID(px, py) and not obstructed[py][px]) \
            { \
                if(px == gx and py == gy) \
                { \
                    visited[gy][gx] = true; \
                    goal_dist = cdist + 1; \
                    goto after; \
                } \
                if(not visited[py][px]) \
                { \
                    visited[py][px] = true; \
                    to_visit.push(make_pair(dt(px, py), cdist + 1)); \
                } \
            }

using namespace std;

struct dt
{
    uint16_t x, y;
    dt(uint16_t _x, uint16_t _y) { x = _x; y = _y; }
};

const size_t MAX = 1000;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint16_t w, h;
    cin >> h >> w;
    uint16_t sx = 0, sy = 0, gx = w - 1, gy = h - 1;
    static array<array<bool, MAX>, MAX> obstructed;
    for(uint16_t y = 0; y < h; y++)
    {
        for(uint16_t x = 0; x < w; x++)
        {
            char c;
            cin >> c;
            if(c == 'x')
                obstructed[y][x] = true;
            else
            {
                if(c == 'z')
                {
                    sx = x; sy = y;
                }
                else if(c == 'n')
                {
                    gx = x; gy = y;
                }
                obstructed[y][x] = false;
            }
        }
    }
    static array<array<bool, MAX>, MAX> visited;
    uint16_t goal_dist = numeric_limits<uint16_t>::max();
    queue<pair<dt, uint16_t> > to_visit;
    to_visit.push(make_pair(dt(sx, sy), 0));
    while(not to_visit.empty())
    {
        pair<dt, uint16_t> cpair = to_visit.front();
        to_visit.pop();
        dt cpos = cpair.first; uint16_t cdist = cpair.second;
        int16_t x = cpos.x, y = cpos.y;
        CONSIDER(x + 1, y + 2); CONSIDER(x + 1, y - 2);
        CONSIDER(x - 1, y + 2); CONSIDER(x - 1, y - 2);
        CONSIDER(x + 2, y + 1); CONSIDER(x + 2, y - 1);
        CONSIDER(x - 2, y + 1); CONSIDER(x - 2, y - 1);
    }
after:
    if(visited[gy][gx])
        cout << goal_dist;
    else
        cout << "NIE";
}
