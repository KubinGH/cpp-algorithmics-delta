#include <bits/stdc++.h>

using namespace std;

const int64_t oo = INT64_MAX / 3 - 0xD;

int main()
{
    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<int64_t>> dist(n+1, vector<int64_t>(n+1, +oo));
    auto update = [&](size_t u, size_t v, int64_t d) {
        dist[v][u] = dist[u][v] = min(dist[u][v], d);
    };
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; int w;
        cin >> u >> v >> w;
        update(u, v, w);
    }

    for(size_t u = 1; u <= n; u++)
        dist[u][u] = 0;
    for(size_t k = 1; k <= n; k++)
        for(size_t u = 1; u <= n; u++)
            for(size_t v = u; v <= n; v++)
                update(u, v, dist[u][k] + dist[k][v]);

    while(q --> 0)
    {
        size_t u, v;
        cin >> u >> v;
        cout << (dist[u][v] == +oo ? -1 : dist[u][v]) << '\n';
    }
}
