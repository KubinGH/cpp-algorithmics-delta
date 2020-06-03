#include <bits/stdc++.h>

using namespace std;

using mask_t = uint32_t;
mask_t ind(size_t i) { return (mask_t)1 << i; }

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<mask_t> graph(n);
    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        graph[u] |= ind(v);
    }

    vector<uint64_t> result(ind(n));
    result[0] = 1;
    for(mask_t mask = 1; mask < ind(n); mask++)
    {
        auto x0 = mask & -mask;
        auto cmask = mask;
        for(auto x = x0; cmask; cmask -= x, x = cmask & -cmask)
            if(not (graph[__builtin_ctz(x)] & mask))
                result[mask] += result[mask ^ x];
    }

    cout << result[ind(n) - 1] << endl;
}
