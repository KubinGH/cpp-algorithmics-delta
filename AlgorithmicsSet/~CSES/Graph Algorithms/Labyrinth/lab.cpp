#include <bits/stdc++.h>

using namespace std;

const size_t nul = SIZE_MAX;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t h, w;
    cin >> h >> w;

    const size_t n = (w+2)*(h+2);
    vector<vector<bool>> open(h+2, vector<bool>(w+2));
    size_t sx = 0, sy = 0, fx = 0, fy = 0;
    for(size_t y = 0; y < h; y++)
    {
        string row;
        cin >> row;
        for(size_t x = 0; x < w; x++)
        {
            open[y+1][x+1] = row[x] != '#';
            if(row[x] == 'A')
                sx = x+1, sy = y+1;
            if(row[x] == 'B')
                fx = x+1, fy = y+1;
        }
    }

    vector<vector<bool>> vis(h+2, vector<bool>(w+2));
    vector<vector<pair<char, pair<size_t, size_t>>>>
        back(h+2, vector<pair<char, pair<size_t, size_t>>>(w+2, {' ', {nul, nul}}));

    queue<pair<size_t, size_t>> que;
    auto maybe = [&](size_t y, size_t x, size_t y1, size_t x1, char d) {
        if(open[y][x] and not vis[y][x])
            back[y][x] = {d, {y1, x1}}, vis[y][x] = true, que.emplace(y, x);
    };
    maybe(sy, sx, sy, sx, ' ');
    while(not que.empty())
    {
        auto [y, x] = que.front(); que.pop();
        maybe(y - 1, x, y, x, 'U'); maybe(y + 1, x, y, x, 'D');
        maybe(y, x - 1, y, x, 'L'); maybe(y, x + 1, y, x, 'R');
    }

    if(vis[fy][fx])
    {
        cout << "YES" << endl;
        string P;
        auto y = fy, x = fx;
        while(not (x == sx and y == sy))
        {
            auto [c, yx] = back[y][x];
            P.push_back(c);
            tie(y, x) = yx;
        }
        reverse(P.begin(), P.end());
        cout << P.size() << endl << P << endl;
    }
    else
        cout << "NO" << endl;
}
