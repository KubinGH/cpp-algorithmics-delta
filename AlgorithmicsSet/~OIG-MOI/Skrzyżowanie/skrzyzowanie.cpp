#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef pair<int32_t, int32_t> pair_i32;

const size_t MAX = 1000000;

int main()
{
    uint32_t n, m, nc, mc;
    scanf("%u %u %u %u", &n, &m, &nc, &mc);
    static bool A[4*MAX];
    for(uint32_t i = 0; i < nc; i++)
    {
        uint32_t p, t;
        scanf("%u %u", &p, &t);
        A[2*MAX+p-t] = true;
    }
    uint32_t r = 0;
    for(uint32_t i = 0; i < mc; i++)
    {
        uint32_t p, t;
        scanf("%u %u", &p, &t);
        if(not A[2*MAX+p-t])
            r++;
    }
    printf("%u", r);
}
