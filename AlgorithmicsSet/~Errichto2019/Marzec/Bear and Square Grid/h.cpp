#include <bits/stdc++.h>

using namespace std;

constexpr int NAX = 512;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    static bool lock[NAX][NAX];

    for(int y = 0; y < n; y++)
    {
        string row;
        cin >> row;
        for(int x = 0; x < n; x++)
            if(row[x] == 'X')
                lock[y][x] = true;
    }

    static bool vis[NAX][NAX];
    static int id[NAX][NAX], sz[NAX*NAX];

    int m = 0;
    for(int sy = 0; sy < n; sy++)
      for(int sx = 0; sx < n; sx++)
    {
        function<void(int, int)> dfs = [&](int x, int y) {
            if(vis[y][x] or lock[y][x])
                return;
            vis[y][x] = true;
            id[y][x] = m;
            sz[m]++;
            if(x)     dfs(x-1, y);
            if(x<n-1) dfs(x+1, y);
            if(y)     dfs(x, y-1);
            if(y<n-1) dfs(x, y+1);
        };
        if(not vis[sy][sx] and not lock[sy][sx])
            m++, dfs(sx, sy);
    }

    static int id_cnt[NAX*NAX];
    int lock_cnt = 0, open_cnt = 0;

    auto in = [&](int x, int y) {
        return 0 <= x and x < n and 0 <= y and y < n;
    };
    auto push = [&](int x, int y) {
        if(not in(x, y))
            return;
        else if(lock[y][x])
            lock_cnt++;
        else if(not id_cnt[id[y][x]]++)
            open_cnt += sz[id[y][x]];
    };
    auto pop = [&](int x, int y) {
        if(not in(x, y))
            return;
        else if(lock[y][x])
            lock_cnt--;
        else if(not --id_cnt[id[y][x]])
            open_cnt -= sz[id[y][x]];
    };
    auto open_push = [&](int x, int y) {
        if(in(x, y) and not lock[y][x]) return push(x, y);
    };
    auto open_pop = [&](int x, int y) {
        if(in(x, y) and not lock[y][x]) return pop(x, y);
    };

    auto borders = [&](int X, int Y, auto f) {
        for(int x = X; x < X + k; x++) f(x, Y-1);
        for(int x = X; x < X + k; x++) f(x, Y+k);
        for(int y = Y; y < Y + k; y++) f(X-1, y);
        for(int y = Y; y < Y + k; y++) f(X+k, y);
    };

    int result = 0;
    for(int Y = 0; Y + k <= n; Y++)
    {
        for(int y = Y; y < Y + k; y++)
            for(int x = 0; x < k; x++)
                push(x, y);

        for(int X = 0; X + k <= n; X++)
        {
            borders(X, Y, open_push);
            result = max(result, open_cnt + lock_cnt);
            borders(X, Y, open_pop);

            for(int y = Y; y < Y + k; y++) pop(X, y);
            for(int y = Y; y < Y + k; y++) push(X + k, y);
        }

        for(int y = Y; y < Y + k; y++)
            for(int x = n-k+1; x <= n; x++)
                pop(x, y);
    }

    cout << result << endl;
}
