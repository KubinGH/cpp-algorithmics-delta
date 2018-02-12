#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;

const size_t MAX = 1000000;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static char buffer[MAX + 1];
    scanf("%s", buffer+1);
    static uint64_t RC[MAX], K[MAX];
    for(uint32_t i = 1; i < n + 1; i++)
    {
        bool zero = buffer[i] == 'N';
        if(i > 0) { RC[i] = RC[i-1]; K[i] = K[i-1]; }
        if(zero)
            K[i] += RC[i];
        else
            RC[i]++;
    }
    uint32_t t;
    scanf("%u", &t);
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint64_t a, b;
        scanf("%llu %llu", &a, &b);

        uint64_t k;
        if(a == 1 and b == n)
            k = K[b];
        else
            k = K[b] - K[a] - (b - a - RC[b] + RC[a]) * RC[a-1];
        printf("%llu\n", k);
    }
}
