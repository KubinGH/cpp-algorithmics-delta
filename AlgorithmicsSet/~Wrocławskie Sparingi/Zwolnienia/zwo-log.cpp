#include <bits/stdc++.h>

using namespace std;

const size_t K = 1 << 20;
bitset<K> reg, sav[16], knapsack;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; uint k;
    cin >> n >> k;

    vector<uint> A; A.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        uint x;
        cin >> x;
        if(x < k)
            A.push_back(x);
    }
    n = A.size();

    size_t result = 0;
    function<void(size_t, size_t, size_t)> divida = [&](size_t l, size_t r, size_t h) {
        if(l == r)
            return;
        if(l+1 == r)
        {
            reg = knapsack; reg <<= K - k; reg >>= K - A[l];
            result += not reg.any();
            return;
        }
        size_t m = (l + r) / 2;

        sav[h] = knapsack;
        for(size_t i = m; i < r; i++)
            reg = knapsack, reg <<= A[i], knapsack |= reg;
        divida(l, m, h + 1);

        knapsack = sav[h];
        for(size_t i = l; i < m; i++)
            reg = knapsack, reg <<= A[i], knapsack |= reg;
        divida(m, r, h + 1);
    };
    knapsack[0] = 1;
    divida(0, n, 0);

    cout << result << endl;
}
