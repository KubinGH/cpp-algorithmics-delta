#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, k;
    cin >> n >> m >> k;

    vector<vector<bool>> wall(n, vector<bool>(m));
    for(size_t i = 0; i < n; i++)
    {
        string S;
        cin >> S;

        for(size_t j = 0; j < m; j++)
            wall[i][j] = S[j] == 'X';
    }

    vector<vector<size_t>> dist(n, vector<size_t>(m, SIZE_MAX));
    dist[0][0] = 0;
    queue<pair<size_t, size_t>> Q;
    Q.emplace(0, 0);

    while(not Q.empty())
    {
        auto [x, y] = Q.front(); Q.pop();

        auto maybe = [&](size_t dx, size_t dy) {
            if(x+dx < n and y+dy < m and dist[x+dx][y+dy] == SIZE_MAX and not wall[x+dx][y+dy])
                dist[x+dx][y+dy] = dist[x][y] + 1, Q.emplace(x+dx, y+dy);
        };
        maybe(+1, 0); maybe(0, +1);
        maybe(-1, 0); maybe(0, -1);
    }

    uint64_t result = UINT64_MAX, cnt = 0;
    auto d0 = n + m - 2, d = dist[n-1][m-1], p = (d - d0) / 2;
    while(k --> 0)
    {
        uint64_t a, b;
        cin >> a >> b;
        auto v = (d0 + p)*a + p*b;
        if(v < result)
            result = v, cnt = 0;
        cnt += v == result;
    }

    cout << result << ' ' << cnt << endl;
}
