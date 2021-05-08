#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, k;
    cin >> n >> k;

    vector<unordered_set<size_t>> graph(n);

    vector<bool> vis(n);
    queue<size_t> que;

    auto maybe = [&](size_t u) {
        if(not vis[u] and graph[u].size() < k)
            vis[u] = true, que.push(u);
    };

    for(size_t u = 0; u < n; u++)
    {
        size_t d;
        cin >> d;
        for(size_t i = 0; i < d; i++)
        {
            size_t v;
            cin >> v;
            graph[u].insert(v);
        }
        maybe(u);
    }

    auto check = [&](size_t s) -> size_t {
        unordered_map<size_t, size_t> mp;
        size_t f = 1; mp[s] = 0;
        for(auto u : graph[s])
            mp[u] = f++;

        const size_t m = mp.size();
        assert(m < 32);
        array<uint32_t, 32> adj = {};
        for(auto [u, i] : mp)
            for(auto [v, j] : mp)
                if(u == v or graph[u].count(v))
                    adj[i] |= 1 << j;

        size_t result = 0;
        for(size_t mask = 0; mask < (1u << m); mask++)
          if(__builtin_popcount(mask) > result)
        {
            auto left = mask;
            for(size_t u = 0; u < m; u++)
                if(mask >> u & 1)
                    left &= adj[u];
            if(left == mask)
                result = __builtin_popcount(mask);
        }
        return result;
    };

    size_t result = 0;
    while(not que.empty())
    {
        auto u = que.front(); que.pop();
        result = max(result, check(u));
        for(auto v : graph[u])
            graph[v].erase(u), maybe(v);
        graph[u].clear();
    }
    assert(accumulate(vis.begin(), vis.end(), 0u) == n);

    cout << result << endl;
}
