#include <bits/stdc++.h>
#include <ktl/math/matrix.cpp>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint64_t MOD = 1e9 + 7;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) { return a * b % MOD; }
} Z;

uint64_t inverse(uint64_t x)
{
    return power(x, MOD - 2, Z);
}

uint64_t factorial(uint64_t n)
{
    uint64_t r = 1;
    for(uint64_t x = 1; x <= n; x++)
        r *= x, r %= MOD;
    return r;
}

uint64_t binom(uint64_t n, uint64_t k)
{
    return factorial(n) * inverse(factorial(k) * factorial(n - k) % MOD) % MOD;
}

matrix<uint64_t> extrapolation_matrix(uint64_t n)
{
    matrix<uint64_t> M(n + 1, n + 1);
    for(size_t i = 0; i < n; i++)
        M(i, i+1) = 1;
    for(size_t i = 0; i <= n; i++)
        M(n, n - i) = (i % 2 ? MOD-1 : 1) * binom(n + 1, i + 1) % MOD;
    return M;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    uint64_t n; size_t k;
    cin >> n >> k;

    auto E = extrapolation_matrix(k + 1);
    matrix<uint64_t> V(1, k + 2);
    for(uint64_t x = 0, s = 0; x <= k + 1; x++)
    {
        s += power(x+1, k, Z); s %= MOD;
        V(x, 0) = s;
    }

    auto mul = matrix_mod_multiplies<uint64_t, MOD>{};

    auto W = mul(power(E, n - 1, mul), V);

    cout << W(0, 0) << endl;
}
