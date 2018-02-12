#include <bits/stdc++.h>
#ifdef _WIN32
#define LLU_FMT "%I64u"
#else
#define LLU_FMT "%llu"
#endif

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

uint64_t square_sum(uint64_t n)
{
    return (n*(n+1)*(2*n+1))/6;
}

int main()
{
    uint32_t n;
    scanf("%u", &n);
    for(uint32_t ni = 0; ni < n; ni++)
    {
        uint64_t k;
        scanf(LLU_FMT, &k);
        uint64_t i, r, s;
        if(k == 1)
            i = 1;
        else
        {
            uint64_t lo = 1, hi = k;
            while(lo < hi)
            {
                uint64_t m = lo + (hi - lo) / 2;
                if(m > 1442255 or square_sum(m) > k)
                    hi = m;
                else
                    lo = m + 1;
            }
            i = lo;
        }
        s = square_sum(i-1);
        r = i*(i-1)/2;
        printf(LLU_FMT"\n", r + (k - s) / i);
    }
}
