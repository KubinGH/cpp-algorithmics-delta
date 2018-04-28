#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define putchar putchar_unlocked
#define getchar getchar_unlocked
#define LLU_FMT "%llu"
#else
#define LLU_FMT "%I64u"
#endif

using namespace std;

typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;

const size_t MAX_K = 13;
const size_t MAX = 250000;

inline uint16_t load_binary(uint16_t bits)
{
    uint16_t a = 0;
    for(uint16_t i = 0; i < bits; i++)
        a <<= 1, a += (getchar() - '0') & 1;
    getchar();
    return a;
}

int main()
{
    uint32_t n; uint16_t k;
    scanf("%u %hu ", &n, &k);
    static uint16_t A[1 << MAX_K]; uint16_t ai = 0;
    static uint32_t C[1 << MAX_K];
    static bool B[1 << MAX_K];
    for(uint32_t i = 0; i < n; i++)
    {
        uint16_t a = load_binary(k);
        if(a == 0) continue;
        if(not B[a])
            A[ai++] = a, B[a] = true;
        C[a]++;
    }
    uint64_t r = 0;
    for(uint16_t i = 0; i < ai; i++)
    {
        r += C[A[i]]*(C[A[i]]-1)/2;
        for(uint16_t j = i+1; j < ai; j++)
            if(A[i] & A[j])
                r += C[A[i]] * C[A[j]];
    }
    printf(LLU_FMT, r);
}
