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
    vector<vector<uint32_t>> children(n);
    vector<uint32_t> parent(n), T; T.reserve(n);
    vector<bool> vis(n);
    queue<uint32_t> Q;
    vis[0] = true; Q.push(0);
    parent[0] = -1u;
    while(not Q.empty())
    {
        uint32_t v = Q.front(); Q.pop();
        T.push_back(v);
        for(uint32_t u : graph[v])
        {
            if(not vis[u])
            {
                vis[u] = true; Q.push(u);
                parent[u] = v;
                children[v].push_back(u);
            }
        }
    }
    reverse(T.begin(), T.end());

    if(k == 1)
    {
        vector<array<uint32_t, 2>> cost(n);
        vector<uint32_t> max_depth(n);
        for(uint32_t v : T)
        {
            vector<uint32_t> d;
            uint32_t best_gain1 = 0;
            for(uint32_t u : children[v])
            {
                cost[v][0] += cost[u][0] + 2;
                best_gain1 = max(best_gain1, cost[u][0] - cost[u][1]);
                d.push_back(max_depth[u] + 1);
            }

            cost[v][1] = cost[v][0] - best_gain1;
            if(not d.empty())
            {
                nth_element(d.begin(), d.end()-1, d.end());
                max_depth[v] = d.end()[-1];
                if(d.size() >= 2)
                {
                    nth_element(d.begin(), d.end()-2, d.end());
                    cost[v][1] = min(cost[v][1], cost[v][0] - d.end()[-1] - d.end()[-2] + 1);
                }
                else
                    cost[v][1] = min(cost[v][1], cost[v][0] - d.end()[-1]);
            }
        }
        cout << min(cost[0][0], cost[0][1]);
    }
    else
    {

    }
}
