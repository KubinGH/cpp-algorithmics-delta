#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e6;
const uint64_t MOD1 = 1e9+7, MOD2 = 1e9+11;

template<uint64_t MOD, uint64_t BASE>
struct basehash
{
    uint64_t H[MAX];
    uint64_t base_pow[MAX];
    basehash(uint32_t n, char* S)
    {
        for(uint32_t i = 0; i < n; i++)
        {
            if(i > 0)
                H[i] = H[i-1] * BASE, H[i] %= MOD;
            H[i] += (uint64_t)(S[i] + 1 - 'a');
            H[i] %= MOD;

            if(i > 0)
                base_pow[i] = (base_pow[i-1] * BASE) % MOD;
            else
                base_pow[i] = 1;
        }
    }
    uint64_t& operator[] (size_t i) { return H[i]; }
    uint64_t interval_hash(size_t i, size_t j)
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - ((H[i-1]*base_pow[j - i + 1]) % MOD)) % MOD;
    }
    uint64_t interval_equals(size_t a, size_t b, size_t x, size_t y)
    {
        return interval_hash(a, b) == interval_hash(x, y);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    static char S[MAX];
    cin >> n >> S;
    static basehash<MOD1, 31> H1(n, S);
    uint32_t m;
    cin >> m;
    for(uint32_t mi = 0; mi < m; mi++)
    {
        uint32_t i, j;
        cin >> i >> j; i--; j--;
        uint32_t x = i + (j-i+1)/2;
        if(H1.interval_equals(i, x-1, x, j))
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }

}
