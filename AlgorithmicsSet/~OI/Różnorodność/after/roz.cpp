#pragma GCC optimize ("-O2")
#include <bits/stdc++.h>
#ifdef _WIN32
#else
#define getchar getchar_unlocked
#endif
#define OBSERVE(a) { C[a]++; if(C[a] == 1) p++; }
#define UNOBSERVE(a) { C[a]--; if(C[a] == 0) p--; }
#define DONE_TICK {                                     \
    if(p > p_max) p_max = p;                            \
    p_sum += p;                                         \
}

using namespace std;

const size_t MAX = 3000, MAX_C = 1e5+1;

void load_uint32(uint32_t* ptr)
{
    char c;
    while('0' <= (c = getchar()) and c <= '9')
    {
        *ptr *= 10;
        *ptr += c - '0';
    }
}

int main()
{
    uint32_t h = 0, w = 0, k = 0;
    load_uint32(&h); load_uint32(&w); load_uint32(&k);
    static uint32_t A[MAX][MAX];
    static uint32_t C[MAX_C];
    uint32_t p = 0, p_max = 0;
    uint64_t p_sum = 0;
    for(uint32_t y = 0; y < h; y++)
    {
        for(uint32_t x = 0; x < w; x++)
        {
            load_uint32(&A[y][x]);
            if(x < k and y < k)
                OBSERVE(A[y][x]);
        }
    }
    DONE_TICK;
    for(uint32_t ix = 0; ix < w - k + 1; ix++)
    {
        if(ix % 2 == 0) // down
        {
            for(uint32_t y = 0; y < h - k; y++)
            {
                for(uint32_t x = ix; x < ix+k; x++)
                {
                    OBSERVE(A[y+k][x]);
                    UNOBSERVE(A[y][x]);
                }
                DONE_TICK;
            }
            if(ix < w - k) for(uint32_t y = h - k; y < h; y++)
            {
                UNOBSERVE(A[y][ix]);
                OBSERVE(A[y][ix+k]);
            }
        }
        else           // up
        {
            for(uint32_t y = h - k; y --> 0; )
            {
                for(uint32_t x = ix; x < ix+k; x++)
                {
                    UNOBSERVE(A[y+k][x]);
                    OBSERVE(A[y][x]);
                }
                DONE_TICK;
            }
            if(ix < w - k) for(uint32_t y = 0; y < k; y++)
            {
                UNOBSERVE(A[y][ix]);
                OBSERVE(A[y][ix+k]);
            }
        }
        if(ix < w - k) DONE_TICK;
    }
    cout << p_max << " " << p_sum;
}
