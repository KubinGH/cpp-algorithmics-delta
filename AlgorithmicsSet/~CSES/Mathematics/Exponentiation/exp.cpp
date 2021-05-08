#include <bits/stdc++.h>

using namespace std;

const uint mod = 1e9 + 7;

template<typename T, typename Tk, typename AssociativeBinaryOp = multiplies<T>>
T power(T n, Tk k, AssociativeBinaryOp f = {}, T r = T(1))
{
    while(k)
    {
        if(k % 2)
            r = f(r, n);
        k /= 2;
        n = f(n, n);
    }
    return r;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t q;
    cin >> q;

    while(q --> 0)
    {
        uint a, b;
        cin >> a >> b;

        cout << power(a, b, [&](uint x, uint y) {
            return (uint64_t) x * y % mod;
        }) << '\n';
    }
}
