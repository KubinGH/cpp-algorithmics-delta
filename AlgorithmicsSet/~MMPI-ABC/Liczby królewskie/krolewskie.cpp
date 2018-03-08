#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

int main()
{
    uint32_t t;
    scanf("%u", &t);
    for(uint32_t i = 0; i < t; i++)
    {
        uint32_t k;
        scanf("%u", &k); k--;
        if(__builtin_popcount(2 * k) % 2 == 0)
            printf("%u\n", 2*k);
        else
            printf("%u\n", 2*k+1);
    }
}
