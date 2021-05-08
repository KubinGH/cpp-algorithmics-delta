#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t mod = 1e9 + 7, inv4 = (mod+1) / 4;
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
    uint64_t n;
    cin >> n;

    cout << (power(2ul, n*n, modmul) + power(2ul, (n*n + 1) / 2, modmul) + 2 * power(2ul, (n*n + 3) / 4, modmul)) * inv4 % mod << endl;
}
