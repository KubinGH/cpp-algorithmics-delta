#include <bits/stdc++.h>
#define filled_row(_y) (((1u<<w)-1) ^ block[_y])

using namespace std;

const size_t MAX_AB = 20, MAX_W = 10, MAX_H = 100;
const uint32_t MOD = 1e9 + 7;

uint32_t bit_get(uint32_t x, uint32_t i) { return x & (1u << i); }
uint32_t bit_set0(uint32_t x, uint32_t i) { return x & ~(1u << i); }
uint32_t bit_set1(uint32_t x, uint32_t i) { return x | (1u << i); }

int main()
{
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  uint32_t t;
  cin >> t;
  while(t --> 0)
  {
    uint32_t h, w, a, b;
    cin >> h >> w >> a >> b;
    static uint32_t block[MAX_H];
    for(uint32_t y = 0; y < h; y++)
    {
        block[y] = 0;
        for(uint32_t x = 0; x < w; x++)
        {
            char c;
            cin >> c;
            if(c == '0')
                block[y] = bit_set1(block[y], x);
        }
    }
    static vector<uint32_t> T[1u << MAX_W];
    for(uint32_t m = 0; m < (1u << w); m++)
    {
        T[m].clear();
        stack<pair<uint32_t, uint32_t>> rec; // f(n) = f(n-2) + f(n-1)
        rec.emplace(0, m);
        while(not rec.empty())
        {
            auto p = rec.top(); rec.pop();
            uint32_t x, mx; tie(x, mx) = p;
            if(x == w)
            {
                T[m].push_back(mx);
                continue;
            }
            if(bit_get(mx, x) and bit_get(mx, x+1))
                rec.emplace(x+2, bit_set0(bit_set0(mx, x), x+1));
            rec.emplace(x+1, mx);
        }
    }
    // vertical, single, horizontal
    static uint64_t A[MAX_H][1u << MAX_W][MAX_AB+1], B[MAX_H][1u << MAX_W][MAX_AB+1][MAX_W+1], C[MAX_H][1u << MAX_W][MAX_AB+1];
    for(uint32_t y = 0; y < h; y++)
    {
        if(y == 0)
            A[0][0][0] = 1;
        else if(y > 0)
        {
            for(uint32_t m = 0; m < (1u << w); m++)
            {
                if((m & (block[y] | block[y-1])) == 0)
                    for(uint32_t c = 0; c <= b; c++)
                        A[y][m][c] = C[y-1][m ^ filled_row(y-1)][c] % MOD;
                else
                    for(uint32_t c = 0; c <= b; c++)
                        A[y][m][c] = 0;
            }
        }
        for(uint32_t m = 0; m < (1u << w); m++)
        {
            for(uint32_t c = 0; c <= b; c++)
                B[y][m][c][0] = A[y][m][c];
            for(uint32_t x = 1; x <= w; x++)
            {
                for(uint32_t c = 0; c <= b; c++)
                    B[y][m][c][x] = B[y][m][c][x-1];
                if(bit_get(m, x-1))
                {
                    for(uint32_t c = 1; c <= b; c++)
                        B[y][m][c][x] += B[y][bit_set0(m, x-1)][c-1][x-1];
                }
            }
        }
        for(uint32_t m = 0; m < (1u << w); m++)
        {
            for(uint32_t c = 0; c <= b; c++)
                C[y][m][c] = 0;
            if((m & block[y]) != 0)
                continue;
            for(uint32_t mx : T[m])
                for(uint32_t c = 0; c <= b; c++)
                    C[y][m][c] += B[y][mx][c][w];
        }
    }
    uint64_t R = 0;
    for(uint32_t c = a; c <= b; c++)
        R += C[h-1][filled_row(h-1)][c];
    cout << R%MOD << "\n";
  }
}
