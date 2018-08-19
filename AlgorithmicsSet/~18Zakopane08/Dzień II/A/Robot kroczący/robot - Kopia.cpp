#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 8192;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    static bool vis[MAX][MAX][4];
    static bool mov[MAX];
    for(uint32_t i = 0; i < n; i++)
        cin >> mov[i];
    int32_t gx, gy;
    cin >> gx >> gy; gx += n; gy += n;
    queue<tuple<uint32_t, uint32_t, uint32_t, uint32_t>> Q;
    Q.emplace(4096, 4096, 0, 0);
    vis[4096][4096][0] = true;
    while(not Q.empty())
    {
        uint32_t x, y, d, h;
        tie(x, y, d, h) = Q.front(); Q.pop();
        cout << "@ " << x << " " << y << " " << d << " " << h << endl;
        if(h >= n)
            continue;
        else if(not mov[h])
        {
            if(d == 0 and not vis[x][y+1][0])
                vis[x][y+1][0] = true, Q.emplace(x, y+1, 0, h+1);
            else if(d == 1 and not vis[x+1][y][1])
                vis[x+1][y][1] = true, Q.emplace(x+1, y, 1, h+1);
            else if(d == 2 and not vis[x][y-1][2])
                vis[x][y-1][2] = true, Q.emplace(x, y-1, 2, h+1);
            else if(d == 3 and not vis[x-1][y][3])
                vis[x-1][y][3] = true, Q.emplace(x-1, y, 3, h+1);
        }
        else
        {
            if(not vis[x][y][(d+3)%4])
                vis[x][y][(d+3)%4] = true, Q.emplace(x, y, (d+3)%4, h+1);
            if(not vis[x][y][(d+1)%4])
                vis[x][y][(d+1)%4] = true, Q.emplace(x, y, (d+1)%4, h+1);
        }
    }
    cout << (vis[gx][gy][0] or vis[gx][gy][1] or
             vis[gx][gy][2] or vis[gx][gy][3] ? "TAK" : "NIE");
}
