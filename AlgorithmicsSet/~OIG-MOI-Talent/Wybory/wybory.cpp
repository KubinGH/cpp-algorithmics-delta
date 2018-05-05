#include <bits/stdc++.h>
#ifdef _WIN32
#else
#define getchar getchar_unlocked
#endif

using namespace std;

typedef unsigned int uint32_t;
typedef int int32_t;

int main()
{
    uint32_t n;
    scanf("%u ", &n);
    int32_t m = 0, r = 0, s = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        char c = getchar();
        if(c == 'S')
            s--;
        else if(c == 'M')
            s++;
        m = min(m, s);
        r = max(r, s - m);
    }
    printf("%d", r);
}
