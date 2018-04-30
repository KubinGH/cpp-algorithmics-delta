#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1024;

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
    uint64_t operator() (size_t i, size_t j)
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - ((H[i-1]*base_pow[j - i + 1]) % MOD)) % MOD;
    }
    uint64_t interval_equals(size_t a, size_t b, size_t x, size_t y)
    {
        return operator() (a, b) == operator() (x, y);
    }
};

int main()
{
    basehash<uint64_t(1e9+7), 313> H(10, "abcdeabcde");
    cout << H(0, 2) << " " << H(5, 7) << endl;
    cout << H(0, 3) << " " << H(5, 8) << endl;
    cout << H(0, 4) << " " << H(5, 9) << endl;
}
