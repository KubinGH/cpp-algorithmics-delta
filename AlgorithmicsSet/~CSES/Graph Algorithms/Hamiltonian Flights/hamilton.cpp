#include <bits/stdc++.h>

using namespace std;

constexpr uint mod = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    array<array<uint, 32>, 32> A = {};

    for(size_t i = 0; i < m; i++)
    {
        size_t u, v;
        cin >> u >> v; u--; v--;
        A[u][v]++;
    }

    static array<array<uint64_t, 32>, 1 << 20> W = {};
    W[1][0] = 1;

    for(size_t mask = 1; mask < (1u << n); mask++)
      for(size_t u = 0; u < n; u++)
        if(mask >> u & 1)
    {
        for(size_t v = 0; v < n; v++)
            W[mask][u] += W[mask ^ (1 << u)][v] * A[v][u];
        W[mask][u] %= mod;
    }

    cout << W[(1<<n) - 1][n - 1] << endl;
}
