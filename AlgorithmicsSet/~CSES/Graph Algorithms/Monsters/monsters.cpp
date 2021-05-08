#include <bits/stdc++.h>

using namespace std;

const size_t N = 1024;

bool open[N][N], vis[N][N];
tuple<char, size_t, size_t> back[N][N];
size_t bad_dist[N][N], dist[N][N];

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    size_t sy = 0, sx = 0;
    vector<pair<size_t, size_t>> bad;
    for(size_t y = 0; y < n; y++)
    {
        string row;
        cin >> row;
        for(size_t x = 0; x < m; x++)
        {
            open[y+1][x+1] = row[x] != '#';
            if(row[x] == 'M')
                bad.emplace_back(y+1, x+1);
            if(row[x] == 'A')
                sy = y+1, sx = x+1;
        }
    }

    for(size_t y = 0; y <= n+1; y++)
        for(size_t x = 0; x <= m+1; x++)
            bad_dist[y][x] = dist[y][x] = SIZE_MAX - 0xD;

    queue<pair<size_t, size_t>> que;
    auto m_maybe = [&](size_t y, size_t x, size_t d) {
        if(not vis[y][x] and open[y][x])
            vis[y][x] = true, bad_dist[y][x] = d, que.emplace(y, x);
    };
    for(auto [y, x] : bad)
        m_maybe(y, x, 0);
    while(not que.empty())
    {
        auto [y, x] = que.front(); que.pop();
        m_maybe(y - 1, x, bad_dist[y][x] + 1); m_maybe(y + 1, x, bad_dist[y][x] + 1);
        m_maybe(y, x - 1, bad_dist[y][x] + 1); m_maybe(y, x + 1, bad_dist[y][x] + 1);
    }

    auto maybe = [&](size_t y, size_t x, char c, size_t y1, size_t x1) {
        if(not get<0>(back[y][x]) and open[y][x])
        {
            dist[y][x] = dist[y1][x1] + 1;
            if(dist[y][x] < bad_dist[y][x])
                back[y][x] = {c, y1, x1}, que.emplace(y, x);
        }
    };
    dist[0][0] = SIZE_MAX; maybe(sy, sx, ' ', 0, 0);
    while(not que.empty())
    {
        auto [y, x] = que.front(); que.pop();
        maybe(y - 1, x, 'U', y, x); maybe(y + 1, x, 'D', y, x);
        maybe(y, x - 1, 'L', y, x); maybe(y, x + 1, 'R', y, x);
    }

    for(size_t cy = 1; cy <= n; cy++)
     for(size_t cx = 1; cx <= m; cx++)
      if((cy == 1 or cy == n or cx == 1 or cx == m) and get<0>(back[cy][cx]))
    {
        size_t y = cy, x = cx;
        string path;
        while(y and x)
        {
            char c; tie(c, y, x) = back[y][x];
            path.push_back(c);
        }
        path.pop_back();
        reverse(path.begin(), path.end());
        cout << "YES" << endl << path.size() << endl << path << endl;
        return 0;
    }

    cout << "NO" << endl;
}
