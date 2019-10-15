#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint64_t MOD = 1e9 + 33;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) { return a * b % MOD; }
} Z;

uint64_t inverse(uint64_t x)
{
    return power(x, MOD - 2, Z);
}

uint64_t q(uint64_t n)
{
    return Z(3, power(2, n - 1, Z));
}

uint64_t p0(uint64_t n)
{
    return Z(inverse(9), q(n) + (n % 2 ? MOD - 3 : 3));
}

uint64_t p1(uint64_t n)
{
    return (p0(n) + (n % 2 ? 1 : MOD - 1)) % MOD;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    uint64_t n;
    size_t k;

    cin >> n >> k;

    vector<pair<uint64_t, char>> force(k);
    for(auto& p : force)
        cin >> p.first >> p.second;

    sort(force.begin(), force.end());

    uint64_t result = 1;

    auto mul = [&](uint64_t x) {
        result = Z(result, x);
    };

    if(not force.empty())
    {
        mul(power(2, force.front().first - 1, Z));
        for(size_t i = 0; i + 1 < force.size(); i++)
        {
            auto left = force[i], right = force[i+1];
            auto d = right.first - left.first + 1;
            if(left.second == right.second)
                mul(p1(d));
            else
                mul(p0(d));
        }
        mul(power(2, n - force.back().first, Z));
    }
    else
        mul(q(n));

    cout << result;
}
