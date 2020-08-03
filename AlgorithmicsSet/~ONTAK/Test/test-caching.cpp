#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("expensive-optimizations")

#define private public
#include <bitset>
#undef private
#include <bits/stdc++.h>

using namespace std;

const size_t N = 2048;

bitset<N> ld(size_t n)
{
    bitset<N> A;
    for(size_t i = 0; i < n; i++)
        A[i] = getchar_unlocked() == '1';
    getchar_unlocked();
    return A;
}

uint f(uint l, uint b, uint u)
{
    return (b ? (not l)^2 : (not u)|((u^l)<<1));
}

constexpr size_t BITS = 8 * sizeof(unsigned long);

uint8_t get_byte(const bitset<N>& bs, int i)
{
    return (bs._M_w[8*i / BITS] >> (8*i % BITS)) & 255;
}

int main()
{
    size_t n, q;
    cin >> n >> q;

    getchar_unlocked();
    vector<bitset<N>> B(n);
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            B[i][j] = (getchar_unlocked() == 'B');
        }
        getchar_unlocked();
    }

    static uint cache[2][256][256];
    for(size_t ls = 0; ls < 2; ls++)
    {
        for(size_t bs = 0; bs < 256; bs++)
        {
            for(size_t us = 0; us < 256; us++)
            {
                uint8_t l = ls, ok = true;
                for(size_t i = 0; i < 8; i++)
                {
                    auto st = f(l, bs>>i&1, us>>i&1);
                    ok &= st >> 1;
                    l = st & 1;
                }
                cache[ls][bs][us] = l | (ok<<1);
            }
        }
    }

    while(q --> 0)
    {
        auto up = ld(n), down = ld(n), left = ld(n), right = ld(n);

        auto curr = up;
        uint ok = true;
        for(size_t i = 0; ok and i < n; i++)
        {
            uint L = left[i];
            for(size_t j = 0; ok and j < n; j++)
            {
                uint st;
                if(j+32 <= n)
                {
                    uint bs = B[i]._M_w[j/32], us = curr._M_w[j/32];
                    st = cache[L   ][bs>> 0&255][us>> 0&255];
                    ok &= st >> 1;
                    st = cache[st&1][bs>> 8&255][us>> 8&255];
                    ok &= st >> 1;
                    st = cache[st&1][bs>>16&255][us>>16&255];
                    ok &= st >> 1;
                    st = cache[st&1][bs>>24&255][us>>24&255];
                    j += 31;
                }
                else if(j+8 <= n)
                {
                    st = cache[L][get_byte(B[i], j/8)][get_byte(curr, j/8)];
                    j += 7;
                }
                else
                {
                    st = f(L, B[i][j], curr[j]);
                }
                ok &= st >> 1;
                L = st & 1;
            }
            ok &= (L == right[i]);
            curr ^= B[i];
        }
        cout << (ok and curr == down ? "YES" : "NO") << endl;
    }
}
