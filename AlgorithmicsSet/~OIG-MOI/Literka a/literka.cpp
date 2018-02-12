#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1000000;

int main()
{
    uint32_t n;
    scanf("%u\n", &n);
    static char S[MAX+1];
    uint32_t ac = 0, a0 = 0, a1 = 0, a2 = 0, start = 0, result = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        S[i] = getchar();
        if(S[i] == 'a')
            ac++, a0 = a1, a1 = a2, a2 = i;
        if(ac == 2)
            start = 0, result = a2;
        else if(ac > 2)
        {
            if(a2 - a0 - 1 > result)
                start = a0+1, result = a2 - a0 - 1;
        }
    }
    if(ac >= 2 and n - a1 - 1 > result)
        start = a1+1, result = n - a1 - 1;
    if(ac <= 1)
        start = 0, result = n;
    printf("%u\n", result);
    for(uint32_t i = 0; i < result; i++)
        putchar(S[start+i]);
}
