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
        graph[v].push_back(u);
    }

    vector<bool> vis(n+1), stk(n+1);
    vector<size_t> stk_list;

    size_t ru = 0, rv = 0;
    function<bool(size_t, size_t)> dfs = [&](size_t u, size_t p) {
        if(vis[u])
            return false;
        vis[u] = stk[u] = true;
        stk_list.push_back(u);
        for(auto v : graph[u])
        {
            if(not vis[v])
            {
                if(dfs(v, u))
                    return true;
            }
            else if(stk[v] and v != p)
            {
                ru = v; rv = u;
                return true;
            }
        }
        stk_list.pop_back();
        stk[u] = false;
        return false;
    };
    for(size_t s = 1; s <= n and not (ru and rv); s++)
        dfs(s, 0);

    if(ru and rv)
    {
        auto first = find(stk_list.begin(), stk_list.end(), ru);
        auto  last = find(stk_list.begin(), stk_list.end(), rv) + 1;
        auto cycle = vector<size_t>(first, last);
        cycle.push_back(cycle.front());
        cout << cycle.size() << endl;
        for(auto u : cycle)
            cout << u << ' ';
        cout << endl;
    }
    else
        cout << "IMPOSSIBLE" << endl;
}
