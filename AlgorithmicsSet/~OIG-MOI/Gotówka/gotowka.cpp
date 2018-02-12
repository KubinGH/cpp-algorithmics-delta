#include <bits/stdc++.h>
#ifdef _WIN32
#define LLU_FMT "%I64d"
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
#define LLU_FMT "%llu"
#endif

using namespace std;

typedef long long int int64_t;
typedef unsigned int uint32_t;

const size_t MAX = 20;
const size_t BINMAX = 1 << MAX;
const uint32_t LIM = 1000000007;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static int64_t A[MAX], S[BINMAX];
    static uint32_t R[BINMAX];
    for(uint32_t i = 0; i < n; i++)
        scanf(LLU_FMT, A+i);
    sort(A, A + n);
    S[0] = R[0] = 0;
    uint32_t a = (1 << n);
    for(uint32_t i = 1; i < a; i++)
    {
        uint32_t b = i;
        if(__builtin_popcount(i) == 1)
        {
            for(uint32_t k = 0; k < n; k++, b /= 2)
                if(b % 2)
                    S[i] += A[n-k-1];
            R[i] = S[i] >= 0;
        }
        else
        {
            for(uint32_t k = 0; k < n; k++, b /= 2)
                if(b % 2)
                    S[i] += A[n-k-1];
            if(S[i] < 0)
                continue;
            b = i;
            for(uint32_t k = 0; k < n; k++, b /= 2)
                if(b % 2 and S[i ^ (1 << k)] + A[n-k-1] >= 0)
                    { R[i] += R[i ^ (1 << k)]; R[i] %= LIM; }
        }
    }
    printf("%u", R[(1 << n) - 1]);
}
