#include <bits/stdc++.h>
#ifdef _WIN32
#define LLU_FMT "%I64u"
#else
#define LLU_FMT "%llu"
#endif // _WIN32

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

const size_t MAX = 1000;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static uint64_t A[MAX][MAX], R[MAX], C[MAX];
    for(uint32_t y = 0; y < n; y++)
    {
        for(uint32_t x = 0; x < n; x++)
        {
            scanf(LLU_FMT, &A[y][x]);
            R[y] += A[y][x];
        }
    }
    for(uint32_t x = 0; x < n; x++)
        for(uint32_t y = 0; y < n; y++)
            C[x] += A[y][x];
    uint64_t r = 0;
    for(uint32_t x = 0; x < n; x++)
        for(uint32_t y = 0; y < n; y++)
            r = max(C[x] + R[y] - A[y][x], r);
    printf(LLU_FMT, r);
}
