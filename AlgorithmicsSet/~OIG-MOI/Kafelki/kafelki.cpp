#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 200000;
const size_t MAX_S = 1000001;

int main()
{
    uint32_t n, m;
    scanf("%u %u", &n, &m);
    static uint32_t X[MAX_S], T[MAX_S];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t x;
        scanf("%u", &x);
        X[x]++;
    }
    for(uint32_t i = 1; i < MAX_S; i++)
    {
        uint32_t x = X[i];
        if(x)
            for(uint32_t k = i; k < MAX_S; k += i)
                T[k] += x;
    }
    for(uint32_t i = 0; i < m; i++)
    {
        uint32_t a, b;
        scanf("%u %u", &a, &b);
        printf("%u\n", T[__gcd(a, b)]);
    }
}
