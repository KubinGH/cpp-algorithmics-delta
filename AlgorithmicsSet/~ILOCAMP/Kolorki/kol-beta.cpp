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

using matrix = vector<modulus_int>;
matrix matrix_mul(uint32_t n, const matrix& A, const matrix& B)
{
    matrix C(n*n);
    for(uint32_t x = 0; x < n; x++)
        for(uint32_t y = 0; y < n; y++)
            for(uint32_t i = 0; i < n; i++)
                C[y*n + x] += A[y*n + i] * B[i*n + x];
    return C;
}
matrix matrix_pow(uint32_t n, matrix A, uint64_t p)
{
    matrix P(n*n);
    for(uint32_t i = 0; i < n; i++)
        P[i*n + i] = 1;
    while(p)
    {
        if(p % 2) P = matrix_mul(n, P, A);
        A = matrix_mul(n, A, A);
        p /= 2;
    }
    return P;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n; uint32_t m;
    cin >> n >> m;
    if(m == 1) { cout << 0; return 0; }
    if(m == 2) { cout << (n%2 == 0 ? 4 : 0); return 0; }
    static modulus_int B[M][M], Bi[M][M];
    B[0][0] = 1;
    for(uint32_t i = 1; i < M; i++)
        for(uint32_t j = 0; j <= i; j++)
            B[i][j] = B[i-1][j-1] + B[i-1][j], Bi[i][j] = modulus_int(1) / B[i][j];

    const uint32_t s = m+1;
    matrix Z(s*s);

    #define I(x, y) ((y)*s + (x))
    for(uint32_t t = 2; t <= m; t++)
        Z[I(t, 0)] += 1;
    for(uint32_t t = 0; t <= m-2; t++)
        Z[I(t, m)] += 1;
    for(uint32_t k = 1; k <= m-1; k++)
    {
        Z[I(k, k)]   += B[m][k] * (B[m][k] - 1) * Bi[m][k];
        Z[I(k-1, k)] += B[m][k] * (B[m][k-1] - k) * Bi[m][k-1];
        Z[I(k+1, k)] += B[m][k] * (B[m][k+1] - (m - k)) * Bi[m][k+1];
        for(uint32_t t = 0; t < k - 1; t++)
            Z[I(t, k)] += B[m][k];
        for(uint32_t t = k + 2; t <= m; t++)
            Z[I(t, k)] += B[m][k];
    }

    matrix P = matrix_pow(s, Z, n - 2);
    static modulus_int I[M];
    for(uint32_t y = 0; y <= m; y++)
        for(uint32_t x = 0; x <= m; x++)
            I[y] += P[I(x, y)] * B[m][x] * (x > 1);

    modulus_int result = power((power(modulus_int(2), m) - (m+1)), n-1);
    result -= I[0] + I[1];
    result *= power(modulus_int(2), m);
    cout << result;
}
