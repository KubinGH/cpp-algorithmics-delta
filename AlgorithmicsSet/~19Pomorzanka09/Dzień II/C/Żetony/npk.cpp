#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;

const size_t NAX = 1 << 12;
const uint MOD = 1e9 + 7;

struct mod_multiplies : multiplies<uint>
{
    uint operator() (uint a, uint b) { return (uint64_t)a*b % MOD; }
};

uint64_t factorial(uint n)
{
    uint64_t r = 1;
    for(uint i = 1; i <= n; i++)
        r *= i, r %= MOD;
    return r;
}

uint64_t inverse(uint n)
{
    return __gnu_cxx::power(n, MOD - 2, mod_multiplies{});
}

int main()
{
    size_t z, c, n;
    cin >> z >> c >> n;
    cout << factorial(z+c+n) * inverse(factorial(z))%MOD * inverse(factorial(c))%MOD * inverse(factorial(n))%MOD << endl;
}
