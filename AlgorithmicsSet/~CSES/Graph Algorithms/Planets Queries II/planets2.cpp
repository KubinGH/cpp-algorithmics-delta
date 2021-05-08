#include <bits/stdc++.h>

using namespace std;

const size_t JUMP = 20;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<size_t> f(n);
    for(auto& u : f)
        cin >> u, u--;

    vector<int> mu(n), sigma(n);
    vector<bool> done(n);
    vector<size_t> when(n), cycle(n), index(n, SIZE_MAX);
    size_t watch = 1, cycles = 1;

    function<int(size_t)> dfs = [&](size_t u) {
        when[u] = watch++;
        int r = 0;
        if(not when[f[u]])
            r = dfs(f[u]);
        done[u] = true;
        if(not done[f[u]])
            sigma[f[u]] = r = when[u] - when[f[u]] + 1, cycle[f[u]] = cycles++;
        if(not r)
            mu[u] = mu[f[u]] + 1;
        sigma[u] = sigma[f[u]];
        cycle[u] = cycle[f[u]];
        index[u] = r;
        return max(r - 1, 0);
    };

    for(size_t s = 0; s < n; s++)
        if(not when[s])
            dfs(s);

    vector<array<size_t, JUMP>> g(n);
    for(size_t u = 0; u < n; u++)
        g[u][0] = f[u];
    for(size_t j = 0; j+1 < JUMP; j++)
        for(size_t u = 0; u < n; u++)
            g[u][j+1] = g[g[u][j]][j];

    auto jump = [&](size_t u, int k) {
        for(size_t j = 0; j < JUMP; j++)
            if(k >> j & 1)
                u = g[u][j];
        return u;
    };
    auto dist = [&](size_t s, size_t t) {
        if(cycle[s] != cycle[t] or mu[s] < mu[t])
            return -1;
        int result = mu[s] - mu[t];
        s = jump(s, mu[s] - mu[t]);
        if(s == t)
            return result;
        if(mu[t])
            return -1;
        result += (sigma[s] + index[t] - index[s]) % sigma[s];
        return result;
    };

    while(q --> 0)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        cout << dist(u, v) << '\n';
    }
}
