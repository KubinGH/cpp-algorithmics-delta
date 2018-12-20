#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const size_t MAX_N = 1 << 20;
const uint64_t MOD = 1e9 + 7;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) { return (a*b) % MOD; }
} M;


// Slowa takie ze pod rzad wystepuje co najwyzej
// k takich samych liter
pair<vector<uint64_t>, vector<uint64_t>> count_rowlim(uint64_t n, uint64_t m, uint64_t k)
{
    vector<uint64_t> X(n+1), S(n+2);
    X[0] = 1, S[1] = 1;
    if(k == 0) return {X, S};
    for(uint32_t i = 1; i <= k; i++)
        X[i] = (X[i-1]*m)%MOD, S[i+1] = (S[i]+X[i])%MOD;
    for(uint32_t i = k+1; i <= n; i++)
    {
        X[i] = ((MOD + S[i] - S[i-k]) * (m - 1)) % MOD;
        S[i+1] = (S[i] + X[i]) % MOD;
    }
    return {X, S};
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint64_t n, m, k;
    cin >> n >> m >> k;
    auto P = count_rowlim(n, m, k-1);
    auto X = P.first; auto S = P.second;
    uint64_t mulm = ((((m-1)*(m-1))%MOD) * power(m, MOD - 2, M)) % MOD;
    for(uint32_t i = k; i <= n; i++)
    {
        uint64_t r = 0;
        if(i == k)
            r = m;
        else
        {
            for(uint32_t j = 1; j+1 <= i - k; j++)
                r += (X[j] * X[i-j-k]) % MOD;
            r %= MOD; r *= mulm; r %= MOD;
            r += (2 * X[0] * X[i-k])%MOD * (m - 1);
        }
        r %= MOD;
        cout << r << "\n";
    }
}
