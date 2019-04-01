#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    uint32_t max_p = 0;
    vector<vector<uint32_t>> loc(n);
    uint32_t source = -1u, target = -1u;
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t b, p;
        cin >> b >> p;
        max_p = max(max_p, p);
        loc[b].push_back(p);
        if(i == 0)
            source = b;
        else if(i == 1)
            target = b;
    }
    for(uint32_t i = 0; i < n; i++)
    {
        sort(loc[i].begin(), loc[i].end());
        loc[i].erase(unique(loc[i].begin(), loc[i].end()), loc[i].end());
    }
    vector<vector<uint32_t>> dist(max_p + 1, vector<uint32_t>(n, -1u));

    queue<pair<uint32_t, uint32_t>> Q;
    auto put = [&](uint32_t b, uint32_t p, uint32_t d) {
        if(dist[p][b] != -1u)
            return;
        dist[p][b] = d;
        Q.emplace(p, b);
    };

    for(uint32_t p : loc[source])
        put(source, p, 0);
    loc[source].clear();

    while(not Q.empty())
    {
        uint32_t p, b;
        tie(p, b) = Q.front(); Q.pop();
        uint32_t d = dist[p][b];
        if(b == target)
        {
            cout << d;
            return 0;
        }

        for(uint32_t p1 : loc[b])
            put(b, p1, d);
        loc[b].clear();

        if(b-p < n) put(b - p, p, d + 1);
        if(b+p < n) put(b + p, p, d + 1);
    }

    cout << -1;
}
