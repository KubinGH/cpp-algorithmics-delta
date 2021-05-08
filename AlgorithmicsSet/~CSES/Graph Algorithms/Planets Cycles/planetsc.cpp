#include <bits/stdc++.h>

using namespace std;

const size_t JUMP = 20;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    cin >> n;

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

    for(size_t u = 0; u < n; u++)
        cout << mu[u] + sigma[u] << ' ';
    cout << endl;
}
