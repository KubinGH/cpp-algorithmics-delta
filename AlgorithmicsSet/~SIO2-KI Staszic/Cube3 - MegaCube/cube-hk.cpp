#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1024;
const uint64_t UMOD = 1e9+21, BASE = 103, ROWBASE = 1971;

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
typedef basehash<uint64_t, UMOD, BASE, MAX> thash;

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
            cin >> A[y][x], A[y][x]++;
        H[y].init(begin(A[y]), begin(A[y]) + w);
    }
    uint64_t SK = 0;
    static uint64_t rowpow[MAX];
    rowpow[0] = 1;
    for(uint32_t i = 1; i <= h; i++)
        rowpow[i] = (rowpow[i-1] * ROWBASE) % UMOD;
    for(uint32_t y = 0; y < ch; y++)
    {
        for(uint32_t x = 0; x < cw; x++)
        {
            uint64_t c;
            cin >> c; c++;
            K[y] *= BASE; K[y] += c; K[y] %= UMOD;
        }
        SK *= ROWBASE; SK += K[y]; SK %= UMOD;
    }
    uint32_t r = 0;
    uint64_t SH = 0;
    for(uint32_t x = 0; x+cw-1 < w; x++)
    {
        SH = 0;
        for(uint32_t cy = 0; cy < ch; cy++)
            SH *= ROWBASE, SH += H[cy](x, x+cw-1), SH %= UMOD;
        for(uint32_t y = 0; y+ch-1 < h; y++)
        {
            if(SH == SK)
                r++;
            SH = (UMOD*UMOD + SH - rowpow[ch-1]*H[y](x, x+cw-1)) % UMOD;
            SH *= ROWBASE; SH += H[y+ch](x, x+cw-1); SH %= UMOD;
        }
    }
    cout << r;
}
