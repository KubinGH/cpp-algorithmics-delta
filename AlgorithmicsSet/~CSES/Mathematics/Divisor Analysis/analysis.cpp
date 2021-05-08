#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t mod = 1e9 + 7;
constexpr auto modmul  = [](uint64_t x, uint64_t y) { return x * y % mod; };
constexpr auto mod1mul = [](uint64_t x, uint64_t y) { return x * y % (mod - 1); };

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

    size_t n;
    cin >> n;

    uint64_t cnt = 1, cnt1 = 1, sum = 1, prod = 1;
    while(n --> 0)
    {
        uint64_t p, e;
        cin >> p >> e;

        prod = modmul(power(prod, e + 1, modmul), power(p, (e * (e + 1) / 2) % (mod - 1) * cnt1, modmul));
        sum = modmul(sum, modmul(mod + power(p, e + 1, modmul) - 1, power((p - 1) % mod, mod - 2, modmul)));
        cnt = modmul(cnt, e + 1);
        cnt1 = mod1mul(cnt1, e + 1);
    }

    cout << cnt << ' ' << sum << ' ' << prod << endl;
}
