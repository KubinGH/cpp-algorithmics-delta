#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const size_t MAX = 200000;
const uint32_t LIM = 1000000009;

int main()
{
    uint32_t n, k;
    scanf("%u %u", &n, &k); k--;
    static uint32_t C[MAX];
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        scanf("%u", &a); a--;
        if(a > 0 and a <= k)
            C[a] += C[a-1];
        else
            C[a]++;
        if(C[a] > LIM)
            C[a] %= LIM;
    }
    printf("%u", C[k]);
}
