#include <bits/stdc++.h>

using namespace std;

bool valid(int x, int y)
{
    return 0 <= x and x < 8 and 0 <= y and y < 8;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int sx, sy;
    cin >> sx >> sy;
    sx--; sy--;

    mt19937 gen(time(0));
    array<array<int, 8>, 8> vis = {};
    for(size_t rep = 0; rep < 32; rep++)
    {
        for(size_t y = 0; y < 8; y++)
            for(size_t x = 0; x < 8; x++)
                vis[y][x] = 0;

        auto moves = [&](int x, int y) {
            vector<pair<int, int>> ret;
            for(auto dx : {-1, +1})
              for(auto dy : {-1, +1})
                for(auto mx : {1, 2})
            {
                auto my = 1 ^ 2 ^ mx;
                int x1 = x + dx*mx, y1 = y + dy*my;
                if(valid(x1, y1) and not vis[x1][y1])
                    ret.emplace_back(x1, y1);
            }
            shuffle(ret.begin(), ret.end(), gen);
            return ret;
        };

        size_t n = 0;
        int cx = sx, cy = sy;
        while(n < 64)
        {
            vis[cx][cy] = ++n;
            size_t best = 999; int bx = -1, by = -1;
            for(auto [x, y] : moves(cx, cy))
                if(moves(x, y).size() < best)
                    best = moves(x, y).size(), bx = x, by = y;
            if(best == 999)
                break;
            cx = bx;
            cy = by;
        }
        if(n == 64)
            break;
    }

    for(size_t y = 0; y < 8; y++, cout << endl)
        for(size_t x = 0; x < 8; x++, cout << ' ')
            cout << vis[x][y];
}
