#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t mod = 1e9 + 7;

int om(uint64_t x) { return x % 2 ? -1 : 1; }
const auto modmul = [](uint64_t a, uint64_t b) { return (a*b) % mod; };

template<typename T, typename Op, typename Tk = size_t>
T power(T n, Tk k, Op f = {}, T r = T(1))
{
    while(k)
    {
        if(k % 2)
            r = f(r, n);
        n = f(n, n);
        k /= 2;
    }
    return r;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    uint64_t n, m, k;
    cin >> n >> m >> k;

    vector<tuple<int, uint64_t, uint64_t>> known(k);
    for(auto& [s, x, y] : known)
    {
        char c;
        cin >> c >> x >> y; x--; y--;
        s = (c == '+' ? +1 : -1);
    }

    uint64_t result = 0;
    for(size_t t = 0; t < 2; t++)
    {
        bool alter = true;
        map<uint64_t, int> sign;
        for(auto [s, x, y] : known)
        {
            s *= om(x);
            if(sign.count(y) and sign[y] != s)
                alter = false;
            else
                sign[y] = s;
        }
        if(alter)
            result += power<uint64_t>(2, m - sign.size(), modmul);
        result %= mod;

        for(auto& [s, x, y] : known)
            swap(x, y);
        swap(n, m);
    }

    set<int> signs;
    for(auto [s, x, y] : known)
        signs.insert(s * om(x) * om(y));
    result += mod - (2 - signs.size());
    result %= mod;

    // done
    cout << result << endl;
}
