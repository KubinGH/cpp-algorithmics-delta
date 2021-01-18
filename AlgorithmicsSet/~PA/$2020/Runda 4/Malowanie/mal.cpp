#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m; uint p;
    cin >> n >> m >> p;

    const uint inv2 = (p + 1) / 2;
    auto M = [&](uint x) {
        return x >= p ? x - p : x;
    };
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
        uint a = 0, b = 0, c = 0, d = 0;
        for(size_t k = 0; k < m; k++)
        {
            a += L[k]; b += L[m-k-1]; c += Z(k, L[k]); d += Z(k, L[m-k-1]);
            a = M(a); b = M(b); c = M(c); d = M(d);
            L1[k+1] = (p + Z(pairs(k+1), L[m]) - (p + Z(k+1, a) + b + d - c)%p) % p;
        }
        swap(L, L1);
    }

    cout << L[m] << endl;
}
