#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    vector<vector<uint32_t>> graph(n);
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    uint32_t lo = 0, hi = n;
    while(lo < hi)
    {
        uint32_t mid = (lo + hi) / 2;
        uint32_t k = n;
        queue<uint32_t> Q;
        vector<uint32_t> deg(n);
        vector<bool> rem(n);
        for(uint32_t u = 0; u < n; u++)
            deg[u] = graph[u].size();
        for(uint32_t u = 0; u < n; u++)
            if(deg[u] < mid)
                Q.push(u), rem[u] = true;
        while(not Q.empty())
        {
            uint32_t u = Q.front(); Q.pop();
            deg[u] = 0; k--;
            for(uint32_t v : graph[u])
                if(--deg[v] < mid and not rem[v])
                    Q.push(v), rem[v] = true;
        }

        if(not k)
            hi = mid;
        else
            lo = mid+1;
    }
    cout << lo-1;
}
