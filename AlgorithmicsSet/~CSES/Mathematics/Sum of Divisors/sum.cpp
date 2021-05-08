#include <bits/stdc++.h>

using namespace std;

const uint mod = 1e9 + 7, inv2 = (mod + 1) / 2;

uint64_t sigma(uint64_t n)
{
    n %= mod;
    return n * (n + 1) % mod * inv2 % mod;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    uint64_t n;
    cin >> n;

    uint64_t result = 0;
    for(uint64_t i = 1, j; i <= n; i = j + 1)
    {
        j = n / (n / i);
        result += (uint64_t) (n / i) % mod * (mod + sigma(j) - sigma(i - 1)) % mod;
        result %= mod;
    }

    cout << result << endl;
}
