#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n, m, l;
    cin >> n >> m >> l;
    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }
    vector<bool> lock(n);
    function<void(size_t)> dfs = [&](size_t u) {
        lock[u] = true;
        for(auto v : graph[u])
            if(not lock[v])
                dfs(v);
    };
    for(size_t i = 0; i < l; i++)
    {
        size_t u;
        cin >> u; u--;
        dfs(u);
    }
    cout << count(lock.begin(), lock.end(), true);
}
