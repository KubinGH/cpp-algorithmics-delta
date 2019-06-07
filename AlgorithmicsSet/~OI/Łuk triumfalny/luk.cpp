#include <bits/stdc++.h>
//#include <ktl/util/debug_macros.cpp>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    size_t n;
    cin >> n;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < n - 1; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<size_t> parent(n), order; order.reserve(n);
    function<void(size_t, size_t)> dfs_root = [&](size_t u, size_t lock) {
        for(auto v : graph[u])
            if(v != lock)
                dfs_root(v, parent[v] = u);
        order.push_back(u);
    };
    dfs_root(0, 0);

    size_t lo = 0, hi = n + 1;
    while(lo < hi)
    {
        int k = (lo + hi) / 2;

        //cdbg << note(k) << endl;

        vector<int> need_delay(n);
        for(auto u : order)
        {
            int e = 0;
            for(auto v : graph[u]) if(parent[u] != v)
                e += need_delay[v];
            need_delay[u] = max(e - k, 0) + 1;
            //cdbg << u << ": " << need_delay[u] << endl;
        }
        int e = 0;

        for(auto v : graph[0])
            e += need_delay[v];

        if(e <= k)
            hi = k;
        else
            lo = k+1;
    }
    cout << lo;
}
