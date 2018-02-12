#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 100000;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static uint32_t A[MAX];
    for(uint32_t i = 0; i < n; i++)
        scanf("%u", A+i);
    int32_t r = 1 << 30;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t b;
        scanf("%u", &b);
        if(b != 0)
            r = min(r, 31 - __builtin_clz(A[i]/b+1));
    }
    printf("%d", r);
}
