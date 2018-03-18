#include <bits/stdc++.h>
#if not(defined(_WIN32))
#define getchar getchar_unlocked
#endif // not

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 1000001;

int main()
{
    uint32_t n;
    scanf("%u ", &n);
    static uint32_t A[MAX];
    bool any = false;
    for(uint32_t i = 0; i < n; i++)
    {
        char c;
        c = getchar();
        A[i] = c == '#';
        if(A[i]) any = true;
        //A[i] = rand() % 2;
    }
    static bool P[MAX];
    fill(P, P + MAX, true);
    P[0] = false; P[1] = false;
    uint32_t r = any;
    uint32_t cs = ceil(sqrt(n)) + 1, css = ceil(sqrt(sqrt(n))) + 1;
    for(uint32_t i = 1; i < n / 2 + 2; i += 2)
    {
        if(i == 1)
            i++;
        if((n + i - 1) / i < r)
            break;
        if(not P[i]) continue;
        if(i < css) for(uint32_t x = i*i; x < n; x += i)
            P[x] = false;
        for(uint32_t b = 0; b < i; b++)
        {
            uint32_t c = 0;
            for(uint32_t x = b; x < n; x += i)
                c += A[x];
            r = max(c, r);
        }
        if(i == 2)
            i--;
    }
    printf("%u", r);
}
