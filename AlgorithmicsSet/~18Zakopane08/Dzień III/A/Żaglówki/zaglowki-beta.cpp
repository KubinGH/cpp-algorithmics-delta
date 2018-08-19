#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 512;

typedef pair<uint32_t, uint32_t> pair_u32;

uint32_t result[MAX][MAX];
bitset<MAX> visited[MAX], on_stack[MAX], type[MAX];

uint32_t h, w;

pair<bool, uint32_t> dfs(uint32_t x, uint32_t y, bool cl = false)
{
    cout << x << " " << y << endl;
    if(not cl and visited[x][y])
        return {true, 0};
    if((x == 0 or x == w+1) or (y == 0 or y == h+1))
        return {true, 1};
    if(on_stack[x][y])
        return {false, -1u};
    on_stack[x][y] = true;
    uint32_t r = -1u;
    if(type[x][y] == 0)
    {
        auto p1 = dfs(x, y+1, cl);
        auto p2 = dfs(x+1, y, cl);
        if(p1.first and p2.first)
            r = min(r, p1.second + p2.second);
        if(not cl) dfs(x, y+1, true), dfs(x+1, y, true);

        auto p3 = dfs(x-1, y, cl);
        auto p4 = dfs(x, y-1, cl);
        if(p3.first and p4.first)
            r = min(r, p3.second + p4.second);
        if(not cl) dfs(x-1, y, true), dfs(x, y-1, true);
    }
    else
    {
        auto p1 = dfs(x, y-1, cl);
        auto p2 = dfs(x+1, y, cl);
        if(p1.first and p2.first)
            r = min(r, p1.second + p2.second);
        if(not cl) dfs(x+1, y, true), dfs(x, y-1, true);

        auto p3 = dfs(x-1, y, cl);
        auto p4 = dfs(x, y+1, cl);
        if(p3.first and p4.first)
            r = min(r, p3.second + p4.second);
        if(not cl) dfs(x, y+1, true), dfs(x-1, y, true);
    }
    on_stack[x][y] = false;
    if(r == -1u)
        return {false, -1u};
    if(not cl) result[x][y] = min(result[x][y], r);
    visited[x][y] = not cl;
    return {true, r + 1};
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> h >> w;
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t x = 0; x < w; x++)
    {
        char c;
        cin >> c;
        type[x+1][y+1] = (c == 'N');
        result[x+1][y+1] = -1u;
    }
    for(uint32_t x = 0; x < w; x++)
      for(uint32_t y = 0; y < h; y++)
    {
        dfs(x+1, y+1);
        for(uint32_t a = 0; a <= w+1; a++)
          for(uint32_t b = 0; b <= h+1; b++)
            on_stack[a][b] = false, visited[a][b] = false;
        cout << endl;
    }
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            int32_t r = result[x+1][y+1];
            cout << (1 + (r != -1))*r << " ";
        }
        cout << "\n";
    }
}
