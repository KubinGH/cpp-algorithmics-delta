#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

const uint64_t MOD = 1e9 + 7;

template<typename T, T MOD>
struct mod_multiplies : multiplies<T>
    { T operator() (const T& a, const T& b) { return ((a%MOD) * (b%MOD)) % MOD; } };
template<typename T, T MOD>
T modpower(T a, T b)
    { return power(a, b, mod_multiplies<uint64_t, MOD>()); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    uint64_t modM = 1, mod2 = 1;
    while(n --> 0)
    {
        uint64_t x;
        cin >> x;
        modM *= x%(MOD-1); mod2 *= x%2;
        modM %= MOD-1; mod2 %= 2;
    }
    uint64_t a = modpower<uint64_t, MOD>(2, (MOD + modM - 2) % (MOD-1));
    mod2 ? a = (a + MOD - 1) % MOD : a++;
    a *= modpower<uint64_t, MOD>(3, MOD - 2); a %= MOD;
    cout << a << "/" << modpower<uint64_t, MOD>(2, (MOD + modM - 2) % (MOD-1));
}
