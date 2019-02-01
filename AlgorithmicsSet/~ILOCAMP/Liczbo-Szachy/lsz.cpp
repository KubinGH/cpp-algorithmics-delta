#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

const uint64_t MOD = 1e9 + 7;

struct mod_multiplies : multiplies<int64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) { return (a*b) % MOD; }
} M;

int main()
{
    uint64_t n, m;
    cin >> n >> m; n--; m--;
    if((2*m - n) % 3 or (2*n - m) % 3 or 2*m < n or 2*n < m) { cout << 0; return 0; }
    vector<uint64_t> F(n+1);
    F[0] = 1;
    for(uint64_t i = 1; i <= n; i++)
        F[i] = M(F[i-1], i);
    uint64_t y = (2*m - n) / 3, x = (2*n - m) / 3;
    cout << (F[(n+m)/3] * power(M(F[x], F[y]), MOD - 2, M)) % MOD;
}
