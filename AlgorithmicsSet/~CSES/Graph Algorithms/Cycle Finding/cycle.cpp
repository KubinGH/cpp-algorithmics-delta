#include <bits/stdc++.h>

using namespace std;

constexpr int64_t oo = INT64_MAX/3 - 0xD;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<tuple<size_t, size_t, int>> edges(m);
    for(auto& [u, v, w] : edges)
        cin >> u >> v >> w;

    vector<int64_t> dist(n+1);
    vector<size_t> back(n+1);
    bool did = false;
    for(size_t i = 0; i < n; i++)
    {
        size_t s = 0;
        for(auto [u, v, w] : edges)
            if(dist[u] + w < dist[v])
                dist[v] = dist[u] + w, back[v] = u, s = v;

        if(i == n - 1 and s)
        {
            vector<bool> vis(n+1);
            vector<size_t> cycle;
            size_t u = s;
            while(not vis[u])
                cycle.push_back(u), vis[u] = true, u = back[u];
            cycle.push_back(u);
            reverse(cycle.begin(), cycle.end());
            while(cycle.front() != cycle.back())
                cycle.pop_back();
            did = true;
            cout << "YES" << endl;
            for(auto v : cycle)
                cout << v << ' ';
            cout << endl;
        }
    }
    if(not did)
        cout << "NO" << endl;
}
