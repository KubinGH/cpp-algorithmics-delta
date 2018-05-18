#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 512;

struct index2d {
    uint32_t x, y;
    index2d() { x = y = 0; }
    index2d(uint32_t x, uint32_t y) : x(x), y(y) {}
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, h;
    cin >> w >> h;
    uint32_t sx, sy, gx, gy;
    cin >> sx >> sy >> gx >> gy;
    static vector<index2d> graph[MAX][MAX][2];
    for(uint32_t iy = 0; iy < 2*h+1; iy++)
    {
        uint32_t y = iy / 2;
        char c;
        if(iy % 2 == 0)
        {
            for(uint32_t x = 0; x < w; x++)
            {
                cin >> c;
                if(c == 'b' or c == 'w')
                {
                    uint32_t t = c == 'b' ? 0 : 1;
                    graph[x][y][t].emplace_back(x+1, y);
                    graph[x+1][y][t].emplace_back(x, y);
                }
            }
        }
        else
        {
            for(uint32_t x = 0; x < 2*w + 1; x++)
            {
                cin >> c;
                if(c == 'b' or c == 'w')
                {
                    uint32_t t = c == 'b' ? 0 : 1;
                    uint32_t x1 = (x+1)/2, x2 = x/2;
                    graph[x1][y][t].emplace_back(x2, y+1);
                    graph[x2][y+1][t].emplace_back(x1, y);
                }
            }
        }
    }
    static bool vis[MAX][MAX][2];
    static uint32_t dist[MAX][MAX][2];
    queue<pair<index2d, bool>> to_vis;
    for(uint32_t t = 0; t < 2; t++)
    {
        vis[sx][sy][0] = 1;
        to_vis.emplace(index2d(sx, sy), t);
    }
    uint32_t r = -1u;
    while(not to_vis.empty())
    {
        index2d u; bool t;
        tie(u, t) = to_vis.front(); to_vis.pop();
        if(u.x == gx and u.y == gy)
        {
            r = dist[gx][gy][t];
            break;
        }
        for(index2d v : graph[u.x][u.y][t])
        {
            if(not vis[v.x][v.y][t^1])
            {
                vis[v.x][v.y][t^1] = 1;
                dist[v.x][v.y][t^1] = dist[u.x][u.y][t] + 1;
                to_vis.emplace(v, t^1);
            }
        }
    }
    cout << r;
}
