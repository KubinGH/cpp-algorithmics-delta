// Jakub Bachurski
// Gang Biciaków - O(qn log n)

#include <bits/stdc++.h>

using namespace std;

const size_t nul = SIZE_MAX;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m, z;
    cin >> n >> m >> z;

    vector<vector<pair<size_t, size_t>>> graph(n+1);
    vector<size_t> item(n, nul);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v; int t;
        cin >> u >> v >> t;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
        item[i] = t;
    }

    vector<pair<size_t, size_t>> parent(n+1, {nul, nul});
    function<void(size_t)> dfs = [&](size_t u) {
        for(auto [v, i] : graph[u])
            if(parent[v].first == nul)
                parent[v] = {u, i}, dfs(v);
    };
    parent[1] = {0, 0}; dfs(1);

    vector<size_t> items; items.reserve(n);
    while(z --> 0)
    {
        char c;
        cin >> c;

        if(c == 'Z')
        {
            size_t u, i;
            cin >> u;

            items.clear();
            while(u != 1)
                tie(u, i) = parent[u], items.push_back(item[i]);
            sort(items.begin(), items.end());
            items.erase(unique(items.begin(), items.end()), items.end());

            cout << items.size() << '\n';
        }
        else if(c == 'B')
        {
            size_t i, t;
            cin >> i >> t;
            item[i] = t;
        }
    }
}
