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
    static bool on[MAX][MAX];
    static char buffer[MAX + 1];
    for(uint32_t y = 0; y < h; y++)
    {
        scanf("%s", buffer);
        for(uint32_t x = 0; x < w; x++)
        {
            on[y][x] = buffer[x] == '#';
        }
    }
    static bool done[MAX][MAX];
    uint32_t max_size = MIN(w, h);
    for(uint32_t y = 0; y < h and max_size > 1; y++)
    {
        for(uint32_t x = 0; x < w and max_size > 1; x++)
        {
            if(on[y][x]) for(uint32_t s = 2; s < max_size + 1; s++)
            {
                for(uint32_t sx = 0; sx < s; sx++)
                    if(not on[y+s-1][x+sx]) goto failure;
                for(uint32_t sy = 0; sy < s; sy++)
                    if(not on[y+sy][x+s-1]) goto failure;
                for(uint32_t sx = 0; sx < s; sx++)
                    done[y+s-1][x+sx] = true;
                for(uint32_t sy = 0; sy < s; sy++)
                    done[y+sy][x+s-1] = true;
                continue;
            failure:
                if(not done[y][x])
                    max_size = s - 1;
                break;
            }
        }
    }
    printf("%u", max_size);
}
