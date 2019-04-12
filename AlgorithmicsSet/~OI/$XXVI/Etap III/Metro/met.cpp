#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, k;
    cin >> n >> k;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < n - 1; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    auto bfs = [&](uint32_t src) {
        vector<bool> vis(n);
        vector<uint32_t> dist(n), prev(n);
        queue<uint32_t> Q;
        Q.push(src); prev[src] = -1u; vis[src] = true;
        while(not Q.empty())
        {
            uint32_t u = Q.front(); Q.pop();
            for(uint32_t v : graph[u])
            {
                if(not vis[v])
                {
                    vis[v] = true;
                    dist[v] = dist[u] + 1;
                    prev[v] = u;
                    Q.push(v);
                }
            }
        }
        return make_pair(dist, prev);
    };

    vector<uint32_t> diameter; diameter.reserve(n);
    uint32_t e, f;
    {
        auto search1 = bfs(0);
        e = max_element(search1.first.begin(), search1.first.end()) - search1.first.begin();
        auto search2 = bfs(e);
        f = max_element(search2.first.begin(), search2.first.end()) - search2.first.begin();
        diameter.push_back(f);
        const auto& prev2 = search2.second;
        {
            uint32_t u = f;
            while(prev2[u] != -1u)
            {
                u = prev2[u];
                diameter.push_back(u);
            }
        }
    }

    vector<bool> vis(n);
    for(uint32_t u : diameter)
        vis[u] = true;

    vector<uint32_t> max_sub_depth(n);
    vector<uint32_t> order; order.reserve(n);

    function<void(uint32_t)> dfs_root = [&](uint32_t u) {
        vis[u] = true;
        max_sub_depth[u] = 0;
        for(uint32_t v : graph[u])
        {
            if(not vis[v])
            {
                dfs_root(v);
                max_sub_depth[u] = max(max_sub_depth[u], max_sub_depth[v] + 1);
            }
        }
        order.push_back(u);
    };

    vector<vector<uint32_t>> for_result(n);

    for(uint32_t u : diameter)
      for(uint32_t v : graph[u])
        if(not vis[v])
    {
        order.clear();
        dfs_root(v);

        for(uint32_t w : order)
            for_result[max_sub_depth[w]].push_back(w);
    }

    for(uint32_t r = 0; r < n; r++)
    {
        if(for_result[r].size() <= k - 2)
        {
            cout << r << " " << for_result[r].size()+2 << endl;
            cout << e+1 << " " << f+1 << " ";
            for(uint32_t u : for_result[r])
                cout << u+1 << " ";
            cout << endl;
            break;
        }
    }
}