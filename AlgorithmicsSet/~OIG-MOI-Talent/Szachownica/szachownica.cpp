#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1000;

int main()
{
    uint32_t h, w;
    scanf("%u %u", &h, &w);
    static bool A[MAX][MAX];
    static uint32_t R[MAX][MAX], C[MAX][MAX];
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            char c;
            scanf(" %c", &c);
            A[y][x] = (c == '#');
            if(x > 0) R[y][x] = A[y][x-1] != A[y][x] ? R[y][x-1] + 1 : 1;
            else R[y][x] = 1;
            if(y > 0) C[y][x] = A[y-1][x] != A[y][x] ? C[y-1][x] + 1 : 1;
            else C[y][x] = 1;
        }
    }
    uint32_t r = 0;
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            uint32_t hi = C[y][x];
            for(uint32_t i = 0; i < R[y][x]; i++)
            {
                r += hi;
                if(i < R[y][x] - 1)
                    hi = min(hi, C[y][x-i-1]);
            }
        }
    }
    cout << r;
}
