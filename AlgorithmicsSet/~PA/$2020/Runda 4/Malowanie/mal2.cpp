#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m; uint p;
    cin >> n >> m >> p;

    const uint inv2 = (p + 1) / 2;
    auto Z = [&](uint x, uint y) {
        return (uint64_t)x * y % p;
    };
    auto pairs = [&](uint x) {
        return Z(Z(x, x+1), inv2);
    };

    vector<uint> L(m+1), L1(m+1);
    for(size_t k = 0; k <= m; k++)
        L[k] = pairs(k);

    for(size_t t = 1; t < n; t++)
    {
        for(size_t k = 0; k < m; k++)
        {
            uint si = 0, sj = 0;
            for(size_t i = 0; i <= k; i++)
            {
                si += Z(k - i + 1, L[i]); si %= p;
                sj += Z(i + 1,  L[m - i - 1]); sj %= p;
            }
            L1[k+1] = (Z(pairs(k+1), L[m]) + 2*p - si - sj) % p;
        }
        swap(L, L1);
    }

    cout << L[m] << endl;
}
