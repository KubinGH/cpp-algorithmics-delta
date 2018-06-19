#include <bits/stdc++.h>
#define for_legal_bitmask(cblock, code)                 \
    for(uint32_t m = 0; m < (1u << w); m++)             \
    {                                                   \
        if((cblock & m) == cblock)                      \
            code;                                       \
    }

using namespace std;

const size_t MAX_W = 10, MAX_H = 100;
const size_t MAX_AB = 21;

const uint32_t MOD = 1e9 + 7;
void domod(uint32_t& x) { x %= MOD; }

uint32_t bit_get(uint32_t x, uint32_t i) { return x & (1u << i); }
uint32_t bit_set0(uint32_t x, uint32_t i) { return x & ~(1u << i); }
uint32_t bit_set1(uint32_t x, uint32_t i) { return x | (1u << i); }
uint32_t bit_set(uint32_t x, uint32_t i, uint32_t s)
{
    if(s == 0)
        return bit_set0(x, i);
    else
        return bit_set1(x, i);
}

int main()
{
  uint32_t t; cin >> t; while(t --> 0) {
    uint32_t h, w, a, b;
    cin >> h >> w >> a >> b;
    static uint32_t block[MAX_H];
    fill(block, block + h, 0);
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            char b;
            cin >> b;
            block[y] = bit_set(block[y], x, !(b - '0'));
        }
    }
    static uint32_t D[MAX_AB][MAX_H][1u << MAX_W];
    for(uint32_t i = 0; i <= b; i++)
      for(uint32_t j = 0; j < h; j++)
        for(uint32_t k = 0; k < (1u << w); k++)
            D[i][j][k] = 0;
    for(uint32_t y = 0; y < h; y++)
      for(uint32_t c = 0; c <= b; c++)
    {
        for(uint32_t m = 0; m < (1u << w); m++)
        {
            uint32_t& d;
            if((block[y] & m) != 0)
                continue;
            if(c == 0 and y == 0 and m == 0)
            {
                d = 1;
            }
            else if(y > 0 and m == 0)
            {
                d = D[c][y-1][((1u<<w)-1) ^ block[y-1]];
            }
            else
            {
                if(c > 0) for(uint32_t x = 0; x < w; x++)
                {
                    if(bit_get(m, x))
                        d += D[c-1][y][bit_set0(m, x)], domod(d);
                }

                for(uint32_t x = 0; x < w - 1; x++)
                {
                    if(bit_get(m, x) and bit_get(m, x + 1))
                        d += D[c][y][bit_set0(bit_set0(m, x), x + 1)], domod(d);
                }

                if(y > 0) for(uint32_t x = 0; x < w; x++)
                {
                    if(bit_get(m, x) and not bit_get(block[y-1], x))
                        d += D[c][y-1][bit_set0((1u << w) - 1, x)], domod(d);
                }
            }
            cout << c << "." << y << "." << bitset<5>(m) << " := " << d << endl;
        }
    }
    uint32_t R = 0;
    for(uint32_t c = a; c <= b; c++)
        R = (R + D[c][h - 1][((1u<<w)-1) ^ block[h-1]]) % MOD;
    cout << "-> " << R << endl;
  }
}
