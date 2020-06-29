#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint64_t Mod = 1e9 + 7;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) const
    {
        return a * b % Mod;
    }
} Zp;

uint64_t inverse(uint x)
{
    return power(x % Mod, Mod - 2, Zp);
}

int main()
{
    uint64_t n, m, a;
    cin >> n >> m >> a;

    if(a > 1)
    {
        uint64_t result = 0, x = 1, y = power(a - 1, m, Zp);

        vector<uint> inv(n + 1); {
            inv[1] = 1;
            for(uint i = 2; i < inv.size(); i++)
                inv[i] = (Mod - Mod/i) * inv[Mod % i] % Mod;
        };

        auto ai = inverse(a - 1);
        for(size_t k = 0; k < n; k++)
        {
            result += x * y;
            result %= Mod;

            x *= (m - k) * inv[k + 1] % Mod;
            x %= Mod;
            y *= ai;
            y %= Mod;
        }
        cout << (Mod + power(a, m, Zp) - result) % Mod << endl;
    }
    else
        cout << '1' << endl;
}
