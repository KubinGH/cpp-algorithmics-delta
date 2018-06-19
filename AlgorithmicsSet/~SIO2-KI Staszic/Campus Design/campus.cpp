#include <bits/stdc++.h>
#define filled_row(_y) (((1u<<w)-1) ^ block[_y])

using namespace std;

const size_t MAX_AB = 20, MAX_W = 10, MAX_H = 100;
const uint32_t MOD = 1e9 + 7;

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

int main()
{
  //ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  static uint64_t F[MAX_W*MAX_H];
  F[0] = 1;
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
    static uint32_t D[MAX_AB+1][MAX_H][1u << MAX_W];
    for(uint32_t c = 0; c <= b; c++)
      for(uint32_t y = 0; y < h; y++)
        for(uint32_t m = 0; m < (1u << w); m++)
    {
        uint32_t& d = D[c][y][m];
        d = 0;
        if(m & block[y])
            continue;
        if(c == 0 and y == 0 and m == 0)
            { d = 1; continue; }
        if(c > 0) for(uint32_t x = 0; x < w; x++)
        {
            if(bit_get(m, x))
                d += D[c-1][y][bit_set0(m, x)], d %= MOD;
        }
        for(uint32_t x = 0; x < w - 1; x++)
        {
            if(bit_get(m, x) and bit_get(m, x+1))
                d += D[c][y][bit_set0(bit_set0(m, x), x+1)], d %= MOD;
        }
        if(y > 0 and (filled_row(y-1) & m) == m)
        {
            d += D[c][y-1][filled_row(y-1) ^ m];
            d %= MOD;
        }
        //cout << c << "@" << y << ":" << m << " := " << d << endl;
    }
    uint64_t R = 0;
    for(uint32_t c = a; c <= b and c <= total_free; c++)
    {
        //R += (uint64_t(D[c][h-1][filled_row(h-1)])
        //      * inv_mod(F[c] * F[(total_free - c) / 2]))
        //      % uint64_t(MOD);
        R += D[c][h-1][filled_row(h-1)];
        R %= MOD;
        cout << c << ": " << D[c][h-1][filled_row(h-1)] << endl;

    }
    cout << R << endl;
  }
}
