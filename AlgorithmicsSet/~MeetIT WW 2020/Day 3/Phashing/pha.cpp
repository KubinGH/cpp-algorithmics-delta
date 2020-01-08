#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<size_t, uint>>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v; uint w;
        cin >> u >> v >> w; u--; v--;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    vector<size_t> dist(n, SIZE_MAX);

    queue<size_t> Q;
    Q.push(0); dist[0] = 0;

    while(not Q.empty())
    {
        auto u = Q.front(); Q.pop();
        for(auto [v, w] : graph[u])
            if(dist[u] + 1 < dist[v])
                dist[v] = dist[u] + 1, Q.emplace(v);
    }


    vector<bool> vis(n);
    vector<vector<pair<size_t, uint>>> sp_graph(n);
    Q.push(n-1); vis[n-1] = true;
    while(not Q.empty())
    {
        auto u = Q.front(); Q.pop();
        for(auto [v, w] : graph[u])
        {
            if(dist[v] + 1 == dist[u])
            {
                sp_graph[v].emplace_back(u, w);
                if(not vis[v])
                    vis[v] = true, Q.emplace(v);
            }
        }
    }

    vector<pair<size_t, uint>> back(n);
    vector<size_t> A, B = {0};
    while(not B.empty())
    {
        swap(A, B);
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        uint w_min = UINT_MAX;
        for(auto u : A)
            for(auto [v, w] : sp_graph[u])
                w_min = min(w_min, w);
        for(auto u : A)
            for(auto [v, w] : sp_graph[u])
                if(w == w_min)
                    B.push_back(v), back[v] = {u, w};
        A.clear();
    }

    vector<uint> out; {
        size_t u = n - 1;
        while(u != 0)
        {
            out.push_back(back[u].second);
            u = back[u].first;
        }
        reverse(out.begin(), out.end());
    }

    cout << out.size() << '\n';
    for(auto x : out) cout << x << ' ';
}
