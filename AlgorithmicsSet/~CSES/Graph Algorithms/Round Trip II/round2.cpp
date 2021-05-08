#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n+1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    for(size_t u = 1; u <= n; u++)
        graph[0].push_back(u);

    size_t c1 = 0, c2 = 0;
    vector<bool> vis(n+1), stk(n+1);
    vector<size_t> stk_list;
    function<bool(size_t)> dfs = [&](size_t u) {
        if(vis[u])
            return false;
        vis[u] = stk[u] = true;
        stk_list.push_back(u);
        for(auto v : graph[u])
        {
            if(not vis[v] and dfs(v))
                return true;
            else if(stk[v])
            {
                c1 = v; c2 = u;
                return true;
            }
        }
        stk[u] = false;
        stk_list.pop_back();
        return false;
    };

    if(dfs(0))
    {
        auto it1 = find(stk_list.begin(), stk_list.end(), c1);
        auto it2 = find(stk_list.begin(), stk_list.end(), c2) + 1;
        vector<size_t> cycle(it1, it2);
        cycle.push_back(cycle.front());
        cout << cycle.size() << endl;
        for(auto u : cycle)
            cout << u << ' ';
        cout << endl;
    }
    else
        cout << "IMPOSSIBLE" << endl;
}
