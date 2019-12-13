#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, q;
    cin >> n >> m >> q;

    vector<vector<size_t>> graph(n);

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        u--; v--;

        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    vector<size_t> component(n);
    size_t curr = 1;
    function<void(size_t)> paint = [&](size_t u) {
        if(component[u]) return;
        component[u] = curr;
        for(auto v : graph[u])
            paint(v);
    };
    for(size_t u = 0; u < n; u++)
        if(not component[u])
            paint(u), curr++;

    vector<size_t> vis(n);
    vector<int> dist(n);

    for(size_t i = 1; i <= q; i++)
    {
        size_t s, t;
        cin >> s >> t;
        s--; t--;

        if(s == t)
        {
            cout << "0\n";
            continue;
        }

        queue<size_t> Q;
        dist[s] = dist[t] = 0;
        vis[s] = 2*i; vis[t] = 2*i+1;
        Q.push(s); Q.push(t);
        size_t iter = 0;
        int result = -1;

        if(component[s] == component[t])
          while(not Q.empty())
        {
            iter++;
            size_t u = Q.front(); Q.pop();
            for(auto v : graph[u])
            {
                if((vis[v] / 2) < i)
                    dist[v] = dist[u] + 1, vis[v] = vis[u], Q.push(v);
                else if(vis[u] != vis[v])
                {
                    result = dist[u] + dist[v] + 1;
                    break;
                }
            }
            if(result != -1)
                break;
        }

        cout << result << '\n';
    }
}
