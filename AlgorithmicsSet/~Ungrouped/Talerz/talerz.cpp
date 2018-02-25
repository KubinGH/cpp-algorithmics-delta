#include <stdio.h>
#include <iostream>
#define MAX 1000
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) (MIN((a), MIN((b), (c))))

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t h, w;
    scanf("%u %u", &h, &w);
    static bool is_on[MAX][MAX];
    uint32_t on = 0;
    static char buffer[MAX + 1];
    for(uint32_t y = 0; y < h; y++)
    {
        scanf("%s", buffer);
        for(uint32_t x = 0; x < w; x++)
        {
            is_on[y][x] = buffer[x] == '#';
            on += is_on[y][x];
        }
    }
    static uint32_t max_square[MAX][MAX];
    for(uint32_t x = 0; x < w; x++)
        max_square[0][x] = is_on[0][x];
    for(uint32_t y = 0; y < h; y++)
        max_square[y][0] = is_on[y][0];
    for(uint32_t y = 1; y < h; y++)
    {
        for(uint32_t x = 1; x < w; x++)
        {
            if(is_on[y][x])
                max_square[y][x] = MIN3(max_square[y][x-1], max_square[y-1][x-1], max_square[y-1][x]) + 1;
            else
                max_square[y][x] = 0;
        }
    }
    static uint32_t max_square_con[MAX][MAX];
    static bool skip[MAX][MAX];
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            if(skip[y][x]) continue;
            uint32_t vx = x, vy = y;
            while(vx+1<w and vy+1<h and max_square[vy][vx] < max_square[vy+1][vx+1])
            {
                skip[vy][vx] = true;
                vy++; vx++;
            }
            uint32_t v = max_square[vy][vx];
            for(uint32_t sy = 0; sy < v; sy++)
                for(uint32_t sx = 0; sx < v; sx++)
                    if(max_square_con[vy-sy][vx-sx] < v)
                        max_square_con[vy-sy][vx-sx] = v;
        }
    }
    uint32_t best = MIN(w, h);
    for(uint32_t y = 0; y < h; y++)
        for(uint32_t x = 0; x < w; x++)
            if(is_on[y][x])
                best = MIN(max_square_con[y][x], best);
    printf("%u", best);
}
