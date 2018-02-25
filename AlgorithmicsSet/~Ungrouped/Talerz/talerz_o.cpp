#include <stdio.h>
#include <algorithm>
#include <iostream>
#define MAX 1000

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
    static bool is_done[MAX][MAX];
    uint32_t done, marked, marked_start, sq;
    uint32_t lo = 1, hi = (w < h ? w : h), s;
    uint32_t best = 1;
    while(lo <= hi)
    {
        s = lo + ((hi - lo) / 2);
        done = 0;
        for(uint32_t y = 0; y < h; y++)
            fill(is_done[y], is_done[y+1], false);
        sq = s*s;
        marked = 0;
        for(uint32_t sx=0;sx<s;sx++) for(uint32_t sy=0;sy<s;sy++)
        {
            if(is_on[sy][sx]) marked++;
        }
        marked_start = marked;
        if(marked == sq)
        {
            for(uint32_t sx=0;sx<s;sx++) for(uint32_t sy=0;sy<s;sy++)
            {
                if(not is_done[sy][sx])
                {
                    done++;
                    is_done[sy][sx] = true;
                }
            }
        }
        bool first = true;
        for(uint32_t x = 0; x < w - s + 1; x++)
        {
            if(not first)
            {
                for(uint32_t y = 0; y < s; y++)
                {
                    marked_start -= is_on[y][x-1];
                    marked_start += is_on[y][x+s-1];
                }
                marked = marked_start;
                if(marked == sq)
                {
                    for(uint32_t sx=0;sx<s;sx++) for(uint32_t sy=0;sy<s;sy++)
                    {
                        if(not is_done[sy][x+sx])
                        {
                            done++;
                            is_done[sy][x+sx] = true;
                        }
                    }
                }
            }
            else first = false;
            for(uint32_t y = 0; y < h - s; y++)
            {
                for(uint32_t sx=0;sx<s;sx++)
                {
                    marked -= is_on[y][x+sx];
                    marked += is_on[y+s][x+sx];
                }
                if(marked == sq)
                {
                    for(uint32_t sx=0;sx<s;sx++) for(uint32_t sy=0;sy<s;sy++)
                    {
                        if(not is_done[y+1+sy][x+sx])
                        {
                            done++;
                            is_done[y+1+sy][x+sx] = true;
                        }
                    }
                }
            }
        }
        if(done == on)
        {
            best = s > best ? s : best;
            lo = s + 1;
        }
        else
        {
            hi = s - 1;
        }

    }
    printf("%u", best);
}
