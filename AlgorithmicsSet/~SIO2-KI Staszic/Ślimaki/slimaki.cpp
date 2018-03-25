#include <bits/stdc++.h>
#define FOR_EACH_VISITABLE(x, y, ax, ay, BLOCK) \
if(y < h - 1)                                   \
    { ax = x; ay = y + 1; BLOCK; }              \
if(x < w - 1)                                   \
    { ax = x + 1; ay = y; BLOCK; }              \
if(x < w - 1 and y > 0)                         \
    { ax = x + 1; ay = y - 1; BLOCK; }          \
if(y > 0)                                       \
    { ax = x; ay = y - 1; BLOCK; }              \
if(x > 0)                                       \
    { ax = x - 1; ay = y; BLOCK; }              \
if(x > 0 and y < h - 1)                         \
    { ax = x - 1; ay = y + 1; BLOCK; }          \

using namespace std;

typedef tuple<uint32_t, uint32_t, uint32_t> dt;

const size_t MAX = 1000;

enum hex_type
{
    open,
    closed,
    cost
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, h, c;
    cin >> w >> h >> c;
    static array<array<hex_type, MAX>, MAX> T;
    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 0; x < w; x++)
            T[y][x] = cost;
    for(uint32_t i = 0; i < c; i++)
    {
        uint32_t x, y; char t;
        cin >> x >> y >> t; x--; y--;
        if(t == 'o')
            T[y][x] = open;
        else if(t == 'x')
            T[y][x] = closed;
    }
    static array<array<uint32_t, MAX>, MAX> D;
    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 0; x < w; x++)
            D[y][x] = -1u;
    priority_queue<dt, vector<dt>, greater<dt>> Q;
    for(uint32_t x = 0; x < w; x++)
    {
        if(T[0][x] != closed)
        {
            D[0][x] = T[0][x] == cost ? 1 : 0;
            Q.emplace(D[0][x], x, 0);
        }
    }
    while(not Q.empty())
    {
        dt current = Q.top(); Q.pop();
        uint32_t d = get<0>(current), x = get<1>(current), y = get<2>(current);
        if(d > D[y][x])
            continue;
        if(y == h - 1)
        {
            cout << d;
            return 0;
        }
        uint32_t cx, cy;
        FOR_EACH_VISITABLE(x, y, cx, cy, {
            if(T[cy][cx] != closed)
            {
                uint32_t a = T[cy][cx] == cost ? 1 : 0;
                if(D[cy][cx] > d + a)
                {
                    D[cy][cx] = d + a;
                    Q.emplace(D[cy][cx], cx, cy);
                }
            }
        })
    }
    cout << "-1";
}
