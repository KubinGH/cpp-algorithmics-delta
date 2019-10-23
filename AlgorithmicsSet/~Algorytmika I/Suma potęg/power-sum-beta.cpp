#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9 + 7;

struct mod_multiplies : multiplies<uint>
{
    uint operator() (uint a, uint b) { return (uint64_t)a*b % MOD; }
} Z;

vector<uint> power_sum(size_t K, uint64_t N)
{
    vector<vector<uint>> choose(K+0xD, vector<uint>(K+0xD));
    choose[0][0] = 1;
    for(uint64_t n = 0; n <= K; n++)
        for(uint64_t k = 0; k <= n; k++)
            choose[n][k] %= MOD, choose[n+1][k] += choose[n][k], choose[n+1][k+1] += choose[n][k];
    function<vector<uint>(uint)> calc = [&](uint n) {
        vector<uint> result(K + 1);
        if(n == 0) {}
        else if(n % 2)
        {
            auto base = calc(n - 1);
            uint x = 1;
            for(size_t k = 0; k <= K; k++)
            {
                result[k] = (base[k] + x) % MOD;
                x = Z(x, n);
            }
        }
        else
        {
            auto base = calc(n / 2);
            vector<uint> powN(K + 1);
            powN[0] = 1;
            for(size_t k = 1; k <= K; k++)
                powN[k] = Z(powN[k-1], n / 2);
            for(size_t k = 0; k <= K; k++)
            {
                uint64_t r = base[k];
                for(size_t i = 0; i <= k; i++)
                    r += Z(choose[k][i], Z(powN[k - i], base[i]));
                result[k] = r % MOD;
            }
        }
        return result;
    };
    return calc(N % MOD);
}

int main()
{
    uint64_t n; size_t k;
    cin >> n >> k;

    auto result = power_sum(k, n);

    cout << result[k];
}
