#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1000;

template<typename T, T MOD, T BASE, size_t N>
struct basehash
{
    T H[N];
    T base_pow[N];
    size_t n;
    basehash() {}
    template<typename Iterator>
    basehash(Iterator begin, Iterator end, T fix = 0) { init(begin, end, fix); }
    template<typename Iterator>
    void init(Iterator begin, Iterator end, T fix = 0)
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
    const T& operator[] (size_t i) const { return H[i]; }
    T operator() (size_t i, size_t j) const
    {
        if(i == 0)
            return H[j];
        else
            return (2*MOD + H[j] - ((H[i-1]*base_pow[j - i + 1]) % MOD)) % MOD;
    }
};
typedef basehash<uint64_t, uint64_t(1e9+21), 103, MAX> thash;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    static uint64_t A[MAX][MAX], K[MAX];
    uint32_t w, h, cw, ch;
    cin >> w >> h >> cw >> ch;
    static thash H[MAX];
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
            cin >> A[y][x];
        H[y].init(begin(A[y]), begin(A[y]) + w);
    }
    for(uint32_t y = 0; y < ch; y++)
    {
        for(uint32_t x = 0; x < cw; x++)
        {
            uint64_t c;
            cin >> c;
            K[y] *= 103; K[y] += c; K[y] %= uint64_t(1e9+21);
        }
    }
    uint32_t r = 0;
    for(uint32_t y = 0; y < h - ch + 1; y++)
    {
        for(uint32_t x = 0; x < w - cw + 1; x++)
        {
            for(uint32_t cy = 0; cy < ch; cy++)
            {
                uint64_t a = H[y+cy](x, x+cw-1), b = K[cy];
                if(a != b)
                    goto after;
            }
            r++;
        after:;
        }
    }
    cout << r;
}
