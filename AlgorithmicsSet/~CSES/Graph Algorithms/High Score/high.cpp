#include <bits/stdc++.h>

using namespace std;

const int64_t oo = INT64_MAX/3 - 0xD;

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<tuple<size_t, size_t, int>> edges(m);
    vector<vector<size_t>> hparg(n+1);
    for(auto& [u, v, w] : edges)
        cin >> u >> v >> w, w = -w, hparg[v].push_back(u);

    vector<bool> reach(n+1);
    function<void(size_t)> dfs = [&](size_t u) {
        if(reach[u])
            return;
        reach[u] = true;
        for(auto v : hparg[u])
            dfs(v);
    };
    dfs(n);

    vector<int64_t> dist(n+1, +oo);
    vector<bool> use(n+1);
    dist[1] = 0;
    for(size_t i = 0; i < n; i++)
    {
        bool any = false;
        fill(use.begin(), use.end(), false);
        for(auto [u, v, w] : edges)
            if(dist[u] < +oo and dist[u] + w < dist[v])
                use[u] = use[v] = any = true, dist[v] = dist[u] + w;
        if(i == n - 1 and any)
        {
            any = false;
            for(size_t u = 1; u <= n; u++)
                if(use[u] and reach[u])
                    any = true;
            if(any)
                dist[n] = 1;
        }
    }

    cout << -dist[n] << endl;
}
