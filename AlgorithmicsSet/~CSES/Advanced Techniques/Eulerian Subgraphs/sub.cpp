#include <bits/stdc++.h>

using namespace std;

const uint64_t mod = 1e9 + 7;

template<typename T, typename Monoid, typename Tk>
T power(T n, Tk k, Monoid f, T r = T(1))
{
    while(k)
    {
        if(k % 2)
            r = f(n, r);
        n = f(n, n);
        k /= 2;
    }
    return r;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> graph(n + 1);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<bool> vis(n + 1);
    size_t c = 0;
    for(size_t s = 1; s <= n; s++)
    {
        if(vis[s])
            continue;
        vector<size_t> tovis;
        tovis.push_back(s); vis[s] = true;
        while(not tovis.empty())
        {
            auto u = tovis.back(); tovis.pop_back();
            for(auto v : graph[u])
                if(not vis[v])
                    tovis.push_back(v), vis[v] = true;
        }
        c++;
    }

    cout << power(uint64_t(2), m - n + c, [](uint64_t a, uint64_t b) { return a*b % mod; }) << endl;
}
