#include <bits/stdc++.h>
#define I(x, y) (((y)*m)+(x))

using namespace std;

const uint64_t MOD = 1e9 + 7;

template<typename T>
void matrix_mul(size_t m, const vector<T>& A, const vector<T>& B, vector<T>& R)
{
    for(register size_t i = 0; i < m; i++)
      for(register size_t k = 0; k < m; k++)
        for(register size_t j = 0; j < m; j++)
    {
        R[I(i, k)] += A[I(j, k)] * B[I(i, j)];
        if(j%8 == (m-1)%8) R[I(i, k)] %= MOD;
    }
}
template<typename T, typename PT>
void matrix_power(size_t m, const vector<T>& M, PT p, vector<T>& R)
{
    for(size_t i = 0; i < m; i++)
      for(size_t j = 0; j < m; j++)
        R[I(i, j)] = (i==j);
    vector<T> Q(m*m), B = M;
    while(p)
    {
        if(p % 2) {
            fill(Q.begin(), Q.end(), 0); matrix_mul(m, R, B, Q); swap(R, Q);
        }
        fill(Q.begin(), Q.end(), 0); matrix_mul(m, B, B, Q); swap(B, Q);
        p /= 2;
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int64_t _a, _b, _c; uint32_t n, p;
    cin >> _a >> _b >> _c >> n >> p;
    uint64_t a = (MOD + _a) % MOD, b = (MOD + _b) % MOD, c = (MOD + _c) % MOD;
    uint32_t m = 3*n+1;
    vector<uint64_t> M(m*m);
    // M[I(col, row)] <=> add <previous> col to <current> row
    // [0, n) - building count from type t
    // [n, 2n) - sum offset X from buildings from type t
    // [2n, 3n) - sum offset Y from buildings from type t
    // 3n - gain prefix sum
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t z;
        cin >> z;
        M[I(i, i)] += 1;            // buildings are kept from last turn
        M[I(i, 3*n)] += c;          // and always generate `c`
        M[I(1*n+i, 3*n)] += a;      // and `a * offset(x)`
        M[I(2*n+i, 3*n)] += b;      // and `b * offset(y)`
        M[I(1*n+i, 1*n+i)] += 1;    // offset(x) is kept from last turn
        M[I(2*n+i, 2*n+i)] += 1;    // offset(y) is kept from last turn
        while(z --> 0)
        {
            uint32_t t; uint64_t q; int64_t _dx, _dy;
            cin >> t >> q >> _dx >> _dy; t--; // when you build `q` times `t` from `i`
            uint64_t dx = (MOD + _dx) % MOD, dy = (MOD + _dy) % MOD;
            M[I(i, t)] += q;                // t-count increases by `i-count * q`
            M[I(i, 1*n+t)] += (q * dx)%MOD; // t-offset(x) increases by `i-count * q * dx`
            M[I(1*n+i, 1*n+t)] += q;        // t-offset(y) increases by `q * i-offset(x)`
            M[I(i, 2*n+t)] += (q * dy)%MOD; // t-offset(y) increases by `i-count * q * dy`
            M[I(2*n+i, 2*n+t)] += q;        // t-offset(y) increases by `q * i-offset(y)`
        }
    }
    M[I(3*n, 3*n)] += 1;            // keep prefix sum from last turn
    for(uint32_t y = 0; y < m; y++)
      for(uint32_t x = 0; x < m; x++)
        M[I(x, y)] %= MOD;
    vector<uint64_t> P(m*m);
    matrix_power(m, M, p, P);
    cout << (4*MOD + P[I(0, 3*n)]) % MOD;
}
