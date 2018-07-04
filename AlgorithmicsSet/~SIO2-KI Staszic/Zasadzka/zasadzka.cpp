// grrr
#include <bits/stdc++.h>
#define PUSH_NEXT(x, y) \
    { visited[x][y] = true; target[x][y] = d + 1; Q.emplace(x, y); }
#define VALID_TILE(x, y) \
    (not visited[x][y] and \
      (level[x][y] == '.' or \
       ('a' <= level[x][y] and level[x][y] <= 'h') or \
       ('A' <= level[x][y] and level[x][y] <= 'H' and \
        ((mask & (1u << (level[x][y] - 'A'))) != 0)) \
       ) \
     )

using namespace std;

const size_t MAX = 200, MAX_KEYS = 8;

struct coor_t
{
    uint32_t x, y;
    coor_t() {}
    coor_t(uint32_t x, uint32_t y) : x(x), y(y) {}
};

void dist_map(uint32_t w, uint32_t h,
              const array<array<char, MAX>, MAX>& level,
              coor_t start, uint32_t mask,
              array<array<uint32_t, MAX>, MAX>& target)
{
    static bitset<MAX> visited[MAX];
    queue<coor_t> Q;
    Q.push(start);
    target[start.x][start.y] = 0;
    visited[start.x][start.y] = 0;
    while(not Q.empty())
    {
        coor_t c = Q.front(); Q.pop();
        uint32_t d = target[c.x][c.y];
        if(c.x > 0 and VALID_TILE(c.x-1, c.y))
            PUSH_NEXT(c.x - 1, c.y);
        if(c.x < w - 1 and VALID_TILE(c.x+1, c.y))
            PUSH_NEXT(c.x + 1, c.y);
        if(c.y > 0 and VALID_TILE(c.x, c.y-1))
            PUSH_NEXT(c.x, c.y - 1);
        if(c.y < h - 1 and VALID_TILE(c.x, c.y+1))
            PUSH_NEXT(c.x, c.y + 1);
    }
}

int main()
{
    uint32_t h, w;
    cin >> h >> w;
    coor_t keys[MAX_KEYS], start, goal;
    bitset<MAX_KEYS> key_exists;
    static array<array<char, MAX>, MAX> level;
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            cin >> level[x][y];
            if('a' <= level[x][y] and level[x][y] <= 'h')
            {
                keys[level[x][y]-'a'] = coor_t(x, y);
                key_exists[level[x][y] - 'a'] = true;
            }
            else if(level[x][y] == 'S')
                start = coor_t(x, y);
            else if(level[x][y] == 'W')
                goal = coor_t(x, y);
        }
    }
    static array<array<uint32_t, MAX>, MAX>
        dist_maps[1u << MAX_KEYS][MAX_KEYS+1];
    for(uint32_t m = 0; m < (1u << MAX_KEYS); m++)
    {
        for(uint32_t k = 0; k < MAX_KEYS+1; k++)
        {
            if(k < MAX_KEYS and not key_exists[k])
                continue;
            dist_map(w, h, level, (k<MAX_KEYS) ? keys[k] : start,
                     m, dist_maps[m][k]);
        }
    }
    for(uint32_t )
}
