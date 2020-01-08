#include <iostream>
#include <climits>
#include <vector>
#include <cassert>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint64_t Mod = 1e9 + 7;

struct mod_multiplies : multiplies<uint64_t>
{
    uint64_t operator() (uint64_t a, uint64_t b) const { return a*b % Mod; }
} Zm;

uint64_t factorial(uint64_t n)
{
    static uint64_t cache[64];
    return cache[n] ? cache[n] : (cache[n] = n ? n * factorial(n - 1) % Mod : 1);
}

uint64_t inverse(uint64_t x)
{
    return power(x, Mod - 2, Zm);
}

uint64_t factorial_inverse(uint64_t n)
{
    static uint64_t cache[64];
    return cache[n] ? cache[n] : (cache[n] = inverse(factorial(n)));
}

// result is divided by factorial(pos)
uint64_t countB(size_t pos, int sum, int lo, size_t m, const vector<int>& Sb_hi)
{
    if(sum > Sb_hi[pos] or sum < 0) return 0;
    if(pos == 0) return 1;

    static uint64_t cache[64][4096][64];
    static bool done[64][4096][64];
    if(done[pos][sum][lo]) return cache[pos][sum][lo];

    uint64_t result = 0;
    for(int value = lo; value <= (int)m; value++)
    {
        bool ok = true;
        for(size_t repeat = 1; repeat <= pos and ok; repeat++)
        {
            auto x = countB(pos - repeat, sum - repeat*value, value+1, m, Sb_hi)
                     * factorial_inverse(repeat) % Mod;
            result += x;

            ok &= (sum - (int)repeat*value <= Sb_hi[pos - repeat]);
        }
    }
    done[pos][sum][lo] = true;
    return cache[pos][sum][lo] = result % Mod;
}

uint64_t countB(size_t n, size_t m, int sum, const vector<int>& Sb_hi)
{
    return countB(n, sum, 0, m, Sb_hi) * factorial(n) % Mod;
}

int main()
{
    size_t n, m;
    cin >> n >> m;

    vector<int> A(m);
    for(auto& a : A)
        cin >> a;

    sort(A.rbegin(), A.rend());

    vector<int> Sa(m+1);
    partial_sum(A.begin(), A.end(), Sa.begin() + 1);
    auto e = Sa[m];

    vector<int> Sb_hi(n+1, INT_MAX);

    // sA + sB ≤ E + |A||B|
    Sb_hi[0] = 0;
    for(size_t i = 1; i <= n; i++)
        for(size_t j = 0; j <= m; j++)
            Sb_hi[i] = min(Sb_hi[i], e + int(i*j) - Sa[j]);

    cout << countB(n, m, e, Sb_hi) << endl;
}
