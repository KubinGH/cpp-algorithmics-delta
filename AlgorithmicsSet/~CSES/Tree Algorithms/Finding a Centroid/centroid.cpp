#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 1; i < n; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> sub(n + 1, 1), parent(n + 1); sub[0] = 0;
    function<void(size_t)> dfs = [&](size_t u) {
        for(auto v : graph[u])
            if(v != parent[u])
                parent[v] = u, dfs(v), sub[u] += sub[v];
    };
    dfs(1);

    size_t c = 1;
    for(size_t u = 1; u <= n; u++)
        if(sub[u] >= (n+1)/2 and sub[u] <= sub[c])
            c = u;

    cout << c << endl;
}
