#include <bits/stdc++.h>

using namespace std;

constexpr uint64_t mod = 1e9 + 7;
constexpr size_t MAX = 1 << 20;

uint modinverse(uint x)
{
    return x > 1 ? (mod - mod/x) * modinverse(mod % x) % mod : x;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    static uint factorial[MAX], inv_factorial[MAX];
    factorial[0] = 1;
    for(uint i = 1; i < MAX; i++)
        factorial[i] = (uint64_t) i * factorial[i - 1] % mod;
    inv_factorial[MAX - 1] = modinverse(factorial[MAX - 1]);
    for(size_t i = MAX - 1; i --> 0; )
        inv_factorial[i] = (uint64_t) (i + 1) * inv_factorial[i + 1] % mod;

    auto binom = [&](uint n, uint k) {
        return k <= n ? (uint64_t) factorial[n] * inv_factorial[k] % mod * inv_factorial[n - k] % mod : 0;
    };

    uint n;
    cin >> n;

    string S;
    cin >> S;

    bool ok = n % 2 == 0;
    int k = 0;
    for(auto c : S)
        if(c == '(')
            k++;
        else if(--k < 0)
            ok = false;
    int m = n - S.size();

    auto cat = [&](uint a, uint b) {
        return (mod + binom(a, b) - binom(a, b - 1)) % mod;
    };

    cout << (ok and k <= m ? cat(m, m/2 - k/2) : 0) << endl;
}
