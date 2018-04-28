#include <bits/stdc++.h>
#ifdef _WIN32
#define LLU_FMT "%I64u"
#else
#define LLU_FMT "%llu"
#endif // _WIN32

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

const size_t MAX = 200000;


int main()
{
    uint32_t n;
    scanf("%u", &n);
    static uint64_t A[MAX], S[MAX+1];
    for(uint32_t i = 0; i < n; i++)
    {
        scanf(LLU_FMT, A + i);
        S[i+1] += S[i] + A[i];
    }
    uint64_t result = 0;
    for(uint32_t i = 1; i < n - 1; i++)
    {
        uint64_t a = S[i], r = S[n] - a;
        if(a >= r) break;
        uint64_t lo_v = ceil(static_cast<long double>(r - a)/2+0.5),
                 hi_v = floor(static_cast<long double>(r + a)/2-0.5);
        if(lo_v > hi_v) continue;
        uint32_t lo = lower_bound(S, S + n, lo_v + a) - S,
                 hi = upper_bound(S, S + n, hi_v + a) - S;
        result += static_cast<uint64_t>(hi - lo);
    }
    printf(LLU_FMT, result);
}
