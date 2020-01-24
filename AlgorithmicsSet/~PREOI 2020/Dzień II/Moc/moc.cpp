#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint64_t Mod = 1e9 + 7;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) const
    {
        return (a * b) % Mod;
    }
} Z;

uint64_t inverse(uint64_t x)
{
    return power(x % Mod, Mod - 2, Z);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; uint64_t k;
    cin >> n >> k;

    vector<uint64_t> A(n+1);
    for(size_t i = 0; i < n; i++)
        cin >> A[i];

    vector<uint64_t> head(n+1);
    head[0] = 1;
    for(size_t i = 0; i < n; i++)
        head[i+1] = (head[i] * A[i] + 1) % Mod;

    vector<uint64_t> P(n+1), invP(n+1);
    P[0] = invP[0] = 1;
    for(size_t i = 0; i < n; i++)
    {
        P[i+1] = P[i] * A[i] % Mod;
        invP[i+1] = inverse(P[i+1]);
    }

    uint64_t result = 0, sum = 0;
    for(size_t i = 0, j = 0; j <= n; sum += A[j], j++)
    {
        while(i < j and sum - A[i] > k)
            sum -= A[i], i++;
        if(sum > k)
            result += invP[i] * P[j] % Mod * head[i] % Mod, result %= Mod;
    }

    cout << result << '\n';
}
