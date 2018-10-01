#include <bits/stdc++.h>

using namespace std;

template<typename T, T MOD, T BASE, size_t N>
struct basehash
{
    T H[N];
    T base_pow[N];
    size_t n;
    template<typename Iterator>
    basehash(Iterator begin, Iterator end, T fix = 0)
    {
        n = distance(begin, end);
        Iterator it = begin;
        for(uint32_t i = 0; i < n; i++)
        {
            if(i > 0)
                H[i] = H[i-1] * BASE, H[i] %= MOD;
            H[i] += T(*it) + fix;
            H[i] %= MOD;

            if(i > 0)
                base_pow[i] = (base_pow[i-1] * BASE) % MOD;
            else
                base_pow[i] = 1;
            it++;
        }
    }
    const uint64_t& operator[] (size_t i) const { return H[i]; }
    uint64_t operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - ((H[i-1]*base_pow[j - i + 1]) % MOD)) % MOD;
    }
};

int main()
{
    char* s = "abcdeabcde";
    basehash<uint64_t, uint64_t(1e9+7), 313, 1024> H(s, s + 10, 0);
    cout << H(0, 2) << " " << H(5, 7) << endl;
    cout << H(0, 3) << " " << H(5, 8) << endl;
    cout << H(0, 4) << " " << H(5, 9) << endl;
}
