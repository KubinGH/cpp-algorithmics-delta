#include <bits/stdc++.h>

using namespace std;

struct vec2d { int32_t x, y; };

const vec2d dirs[] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
enum terrain { wall, road };

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t w, h;
    cin >> w >> h;
    vector<vector<terrain>> T(w, vector<terrain>(h, terrain::road));
    vec2d start = {0, 0}, finish = {0, 0};
    for(int32_t y = 0; y < (int)h; y++)
    {
        string row;
        cin >> row;
        for(int32_t x = 0; x < (int)
        w; x++)
        {
            if(row[x] == '#')
                T[x][y] = terrain::wall;
            else if(row[x] == 'P')
                start = {x, y};
            else if(row[x] == 'W')
                finish = {x, y};
        }
    }
    vector<vector<uint32_t>> dist(w, vector<uint32_t>(h, -1u));
    queue<vec2d> Q;
    Q.push(start); dist[start.x][start.y] = 0;
    while(not Q.empty())
    {
        vec2d c = Q.front(); Q.pop();
        for(uint32_t i = 0; i < 4; i++)
        {
            vec2d d = {c.x + dirs[i].x, c.y + dirs[i].y};
            if(0 <= d.x and d.x < (int)w and 0 <= d.y and d.y < (int)h and
               T[d.x][d.y] == road and dist[d.x][d.y] == -1u)
                dist[d.x][d.y] = dist[c.x][c.y] + 1, Q.push(d);
        }
    }
    if(dist[finish.x][finish.y] == -1u)
        cout << "NIE";
    else
        cout << dist[finish.x][finish.y];
}
