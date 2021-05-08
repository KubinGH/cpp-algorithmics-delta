#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, root, start;
    cin >> n >> root >> start; root--; start--;

    vector<vector<size_t>> graph(n);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    if(start == root)
    {
        cout << '0' << endl;
        return 0;
    }

    vector<size_t> parent(n, SIZE_MAX);
    vector<int> depth(n), degree(n), simcost(n);
    function<void(size_t)> dfs = [&](size_t u) {
        degree[u] = graph[u].size() - (u != root);
        simcost[u] += degree[u] - 1;
        for(auto v : graph[u]) if(v != parent[u])
        {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            simcost[v] += simcost[u];
            dfs(v);
        }
    };
    dfs(root);

    vector<size_t> path;
    size_t curr = start;
    while(curr != root)
        path.push_back(curr), curr = parent[curr];

    vector<int> cost(n, -1);
    function<void(size_t)> get = [&](size_t u) {
        if(cost[u] != -1)
            return cost[u];
        int c[2] = {};
        for(auto v : graph[u]) if(v != parent[u])
        {
            get(v);
            if(cost[v] >= c[0])
                c[1] = c[0], c[0] = cost[v];
            else if(cost[v] > c[1])
                c[1] = cost[v];
        }
        return cost[u] = c[1] + degree[u];
    };
    get(root);

    vector<pair<int, size_t>> subs;
    for(size_t i = 0; i < path.size(); i++)
    {
        auto u = path[i], u1 = i ? path[i-1] : SIZE_MAX;
        for(auto v : graph[u])
            if(v != parent[u] and v != u1)
                subs.emplace_back(simcost[u] + cost[v] - (i>0), i);
    }

    sort(subs.rbegin(), subs.rend());
    size_t result = 0;
    for(size_t r = 0; r <= subs.size(); r++)
    {
        vector<int> rekt(path.size());
        for(size_t i = 0; i < r; i++)
        {
            auto [w, l] = subs[i];
            for(size_t j = l; j < path.size(); j++)
                rekt[j]++;
        }
        bool ok = true;
        for(size_t j = 0; j < path.size(); j++)
            if(rekt[j] > (int)j + 1)
                ok = false;
        if(ok)
            result = (r<subs.size() ? subs[r].first : 0) + r;
    }

    cout << result << endl;
}
