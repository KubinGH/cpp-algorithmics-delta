#include <bits/stdc++.h>
#ifdef _WIN32
#define LLU_FMT "%I64u"
#else
#define LLU_FMT "%llu"
#endif

using namespace std;

typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;

const size_t MAX = 5e5;

uint64_t max(uint64_t a, uint64_t b)
{
    return a > b ? a : b;
}

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static uint64_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        scanf(LLU_FMT, A+i);
    uint64_t r = 0;
    for(uint32_t t = 0; t < n; t++)
    {
        for(uint32_t i = 0; i < n - t; i++)
        {
            r += A[i];
            A[i] = max(A[i], A[i+1]);
        }
    }
    printf(LLU_FMT, r);
}
