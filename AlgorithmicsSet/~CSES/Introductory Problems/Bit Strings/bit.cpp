#include <bits/stdc++.h>

using namespace std;

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

    uint64_t n;
    cin >> n;

    cout << power(2, n, [&](uint64_t x, uint64_t y) {
        return (x * y) % uint64_t(1e9 + 7);
    }) << endl;
}
