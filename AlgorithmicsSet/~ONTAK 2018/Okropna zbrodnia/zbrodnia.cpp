#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1 << 19;

template<typename T, T MOD, T BASE, size_t N>
struct rolling_hash
{
    T H[N];
    T base_pow[N];
    size_t n;
    template<typename Iterator>
    rolling_hash(Iterator first, Iterator last, T fix = 0)
    {
        n = distance(first, last);
        auto it = first;
        for(size_t i = 0; i < n; i++, it++)
        {
            H[i] = T(*it) + fix;
            if(i)
                H[i] += BASE * H[i-1], base_pow[i] = BASE * base_pow[i-1];
            else
                base_pow[i] = 0;
            H[i] %= MOD, base_pow[i] %= MOD;
        }
    }
    const T& operator[] (size_t i) const { return H[i]; }
    T operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - (H[i-1] * base_pow[j - i + 1])%MOD) % MOD;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static char S[MAX];
    cin >> S;
    uint32_t n = strlen(S);
    rolling_hash<uint64_t, uint64_t(1e9+33), 31LLU, MAX>
        H(S, S + n, -uint64_t('a' - 1));
    for(uint32_t d = 1; d < n; d++)
    {
        uint64_t h = H(0, d-1);
        for(uint32_t i = d; i < n; i += d)
        {

        }
    }
}
