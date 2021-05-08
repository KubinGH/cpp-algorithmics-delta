#include <bits/stdc++.h>

using namespace std;

constexpr uint mod = 1e9 + 7;
constexpr auto modmul = [](uint64_t x, uint64_t y) { return x * y % mod; };

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
    uint n, k;
    cin >> n >> k;

    uint64_t result = 0;
    for(uint i = 1; i <= n; i++)
        result += power(k, gcd(i, n), modmul);

    cout << result % mod * power(n, mod - 2, modmul) % mod << endl;
}
