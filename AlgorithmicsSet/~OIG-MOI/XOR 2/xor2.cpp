#include <bits/stdc++.h>
#ifdef _WIN32
#define LLU_FMT "%I64u"
#else
#define LLU_FMT "%llu"
#endif

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

uint64_t sxor(uint64_t n)
{
    switch(n % 4)
    {
        case 0:
            return n; break;
        case 1:
            return 1; break;
        case 2:
            return n + 1; break;
        case 3:
            return 0; break;
    }
}

int main()
{
    uint64_t t;
    scanf(LLU_FMT, &t);
    for(uint64_t ti = 0; ti < t; ti++)
    {
        uint64_t n, m;
        scanf(LLU_FMT " " LLU_FMT, &n, &m);
        printf(LLU_FMT "\n", sxor(n - 1) ^ sxor(m));
    }
}
