#include <functional>
#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <map>

using namespace std;

struct dt { int a, b, c; size_t i; };

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

    vector<dt> E(n);
    for(size_t i = 0; i < n; i++)
        cin >> E[i].a;
    for(size_t i = 0; i < n; i++)
        cin >> E[i].b;
    for(size_t i = 0; i < n; i++)
        cin >> E[i].c;
    for(size_t i = 0; i < n; i++)
        E[i].i = i;

    vector<vector<size_t>> graph(n);
    for(size_t t = 0; t < 3; t++)
    {
        for(size_t i = 0; i < n; i++)
            if(t == 1) swap(E[i].b, E[i].c);
            else if(t == 2) swap(E[i].a, E[i].c);

        sort(E.begin(), E.end(), [&](const auto& lhs, const auto& rhs) {
            return tie(lhs.a, lhs.b) < tie(rhs.a, rhs.b);
        });

        vector<dt> st = {{INT_MAX, INT_MAX, INT_MAX, SIZE_MAX}};
        for(auto& e : E)
        {
            auto itb = lower_bound(st.begin(), st.end(), e,
                [&](const auto& lhs, const auto& rhs) {
                    return lhs.b > rhs.b;
            });
            for(auto it = itb; it != st.end(); ++it)
                graph[it->i].push_back(e.i);
            st.insert(itb, e);
        }

        for(size_t i = 0; i < n; i++)
            if(t == 1) swap(E[i].b, E[i].c);
            else if(t == 2) swap(E[i].a, E[i].c);
    }


    map<size_t, vector<bool>> cache;
    vector<bool> vis(n);
    function<void(size_t)> dfs = [&](size_t u) {
        vis[u] = true;
        for(auto v : graph[u])
            if(not vis[v])
                dfs(v);
    };

    size_t m;
    cin >> m;

    while(m --> 0)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;

        if(not cache.count(u))
        {
            fill(vis.begin(), vis.end(), false);
            dfs(u);
            cache[u] = vis;
        }
        cout << (cache[u][v] ? "TAK\n" : "NIE\n");
    }
}
