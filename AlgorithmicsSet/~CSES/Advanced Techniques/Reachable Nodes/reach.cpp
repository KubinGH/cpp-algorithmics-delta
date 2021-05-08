#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#pragma GCC target ("popcnt,avx,avx2")

using namespace std;

constexpr size_t word_size = 4096;
using word_t = bitset<word_size>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u].push_back(v);
    }

    vector<bool> vis(n);
    vector<size_t> order;
    function<void(size_t)> dfs = [&](size_t u) {
        if(vis[u])
            return;
        vis[u] = true;
        for(auto v : graph[u])
            dfs(v);
        order.push_back(u);
    };
    for(size_t u = 0; u < n; u++)
        dfs(u);

    vector<word_t> words(n);
    vector<size_t> total(n);
    for(size_t k = 0; k*word_size < n; k++)
    {
        for(auto u : order)
        {
            words[u].reset();
            for(auto v : graph[u])
                words[u] |= words[v];
            if(u >= k*word_size and u < (k+1)*word_size)
                words[u].set(u % word_size);
            total[u] += words[u].count();
        }
    }
    for(size_t u = 0; u < n; u++)
        cout << total[u] << ' ';
    cout << endl;
}
