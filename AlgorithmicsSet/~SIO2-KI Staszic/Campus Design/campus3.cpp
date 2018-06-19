#include <bits/stdc++.h>

using namespace std;

const size_t MAX_AB = 20, MAX_W = 10, MAX_H = 100;
const uint32_t MOD = 1e9 + 7;
const uint32_t POW3[MAX_W+1] = {
    1, 3, 9, 27, 81, 243, 729,
    2187, 6561, 19683, 59049
};

uint64_t fast_pow(uint64_t a, uint64_t b)
{
    uint64_t r = 1;
    while(b)
    {
        if(b % 2 == 1)
            r *= a, r %= MOD;
        b /= 2;
        a *= a; a %= MOD;
    }
    return r;
}
uint64_t inv_mod(uint64_t x) { return fast_pow(x % MOD, MOD - 2); }
uint32_t bit_get(uint32_t x, uint32_t i) { return x & (1u << i); }
uint32_t bit_set0(uint32_t x, uint32_t i) { return x & ~(1u << i); }
uint32_t bit_set1(uint32_t x, uint32_t i) { return x | (1u << i); }
uint32_t tri_get(uint32_t x, uint32_t i) { return (x / POW3[i]) % 3; }
uint32_t tri_set(uint32_t x, uint32_t i, uint32_t v)
{
    x -= tri_get(x, i) * POW3[i];
    x += v * POW3[i];
    return x;
}
uint32_t tri_filled_row(uint32_t w, uint32_t b, uint32_t v = 2)
{
    uint32_t x = 0;
    for(uint32_t i = 0; i < w; i++)
        if(not bit_get(b, i))
            x += v*POW3[i];
    return x;
}

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  static uint64_t F[MAX_W*MAX_H];
  F[0] = 0;
  for(uint64_t i = 1; i < MAX_W*MAX_H; i++)
      F[i] = (F[i-1] * i) % uint64_t(MOD);
  uint32_t t;
  cin >> t;
  while(t --> 0)
  {
    uint32_t h, w, a, b;
    cin >> h >> w >> a >> b;
    static uint32_t block[MAX_H];
    uint32_t total_free = 0;
    for(uint32_t y = 0; y < h; y++)
    {
        block[y] = 0;
        for(uint32_t x = 0; x < w; x++)
        {
            char c;
            cin >> c;
            if(c == '0')
                block[y] = bit_set1(block[y], x);
            else
                total_free++;
        }
    }
    static uint32_t D[MAX_AB+1][MAX_H][59049];
    for(uint32_t c = 0; c <= b; c++)
      for(uint32_t y = 0; y < h; y++)
        for(uint32_t t = 0; t < POW3[w]; t++)
    {
        uint32_t m = 0, prev_m = 0;
        for(uint32_t x = 0; x < w; x++)
        {
            if(tri_get(t, x) >= 1)
                prev_m = bit_set1(prev_m, x);
            if(tri_get(t, x) == 2)
                m = bit_set1(m, x);
        }
        uint32_t& d = D[c][y][t];
        d = 0;
        if((m & block[y]) or
           (y > 0 and (m_prev & block[y-1])) or
           (y == 0 and m_prev))
            continue;
        if(c == 0 and y == 0 and m == 0)
            { d = 1; continue; }
        if(y > 1 and t == 0)
            { d = D[c][y-1][tri_filled_row(w, block[y-1])}
        if(c > 0) for(uint32_t x = 0; x < w; x++)
        {
            if(tri_get(t, x) == 2)
                d += D[c-1][y][tri_set(t, x, 1)], d %= MOD;
        }
        for(uint32_t x = 0; x < w - 1; x++)
        {
            if(tri_get(t, x) == 2 and tri_get(t, x+1) == 2)
                d += D[c][y][tri_set(tri_set(t, x, 1), x+1, 1)], d %= MOD;
        }
        if(y > 0) for(uint32_t x = )

    }
  }
}
