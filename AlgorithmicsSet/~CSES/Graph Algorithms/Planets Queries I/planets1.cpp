#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<array<size_t, 32>> f(n);
    for(size_t i = 0; i < n; i++)
        cin >> f[i][0], f[i][0]--;

    for(size_t j = 0; j < 31; j++)
        for(size_t u = 0; u < n; u++)
            f[u][j+1] = f[f[u][j]][j];

    while(q --> 0)
    {
        size_t u; uint64_t k;
        cin >> u >> k; u--;
        for(size_t j = 32; j --> 0; )
            if(k >> j & 1)
                u = f[u][j];
        cout << u+1 << '\n';
    }
}
