#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

const size_t N = 1 << 15, M = 64;
const uint64_t MOD = 1e9 + 7;

uint32_t p(uint32_t x) { return __builtin_popcount(x); }
uint64_t modi(uint64_t x) { return x < MOD ? x : x % MOD; }
uint64_t safeminus(uint64_t a, uint64_t b) { return MOD + a - b; }
struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) const { return ((a%MOD)*(b%MOD))%MOD; }
};
uint64_t modidiv(uint64_t x, uint64_t y) { return (x%MOD) * power(y%MOD, MOD - 2, mod_multiplies()); }

struct modulus_int
{
    uint64_t n;
    modulus_int() : n(0) {}
    modulus_int(uint64_t _n) : n(_n % MOD) {}
    #define ARITHMETIC(__op, __func) \
        modulus_int __op (const modulus_int& o) const { return modi(__func(n, o.n)); } \
        modulus_int __op (const uint64_t& o) const { return modi(__func(n, o)); }
    ARITHMETIC(operator+, plus<uint64_t>());
    ARITHMETIC(operator-, safeminus);
    ARITHMETIC(operator*, multiplies<uint64_t>());
    ARITHMETIC(operator/, modidiv);
    #undef ARITHMETIC
    #define INPLACE_ARITHMETIC(__inplace_op, __op) \
        modulus_int& __inplace_op (const modulus_int& o) { return *this = __op(o); }
    INPLACE_ARITHMETIC(operator+=, operator+);
    INPLACE_ARITHMETIC(operator-=, operator-);
    INPLACE_ARITHMETIC(operator*=, operator*);
    #undef INPLACE_ARITHMETIC
};
ostream& operator<< (ostream& out, const modulus_int& o)
{
    return out << o.n;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    if(m == 1) { cout << 0; return 0; }
    if(m == 2) { cout << (n%2 == 0 ? 4 : 0); return 0; }
    static modulus_int B[M][M], Bi[M][M];
    B[0][0] = 1;
    for(uint32_t i = 1; i < M; i++)
        for(uint32_t j = 0; j <= i; j++)
            B[i][j] = B[i-1][j-1] + B[i-1][j], Bi[i][j] = modulus_int(1) / B[i][j];
    static modulus_int I[N][M], S[N][M];

    for(uint32_t t = 0; t <= m; t++)
    {
        I[2][t] = B[m][t] * (t > 1);
        S[2][t+1] = S[2][t] + I[2][t];
    }
    for(uint32_t i = 3; i <= n; i++)
    {
        for(uint32_t t = 2; t <= m; t++)
            I[i][0] += I[i-1][t];
        for(uint32_t t = 0; t <= m-2; t++)
            I[i][m] += I[i-1][t];
        for(uint32_t k = 1; k <= m-1; k++)
        {
            I[i][k] = (
                I[i-1][k]   * (B[m][k] - 1) * Bi[m][k] +
                I[i-1][k-1] * (B[m][k-1] - k) * Bi[m][k-1] +
                I[i-1][k+1] * (B[m][k+1] - (m - k)) * Bi[m][k+1]
            );
            I[i][k] += S[i-1][k-1];
            I[i][k] += S[i-1][m+1] - S[i-1][k+2];
            I[i][k] *= B[m][k];
        }
        for(uint32_t t = 0; t <= m; t++)
            S[i][t+1] = S[i][t] + I[i][t];
    }
    modulus_int result = power((power(modulus_int(2), m) - (m+1)), n-1);
    result -= I[n][0] + I[n][1];
    result *= power(modulus_int(2), m);
    cout << result;
}
