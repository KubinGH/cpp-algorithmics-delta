#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;

const uint32_t MAX = 5001;
const uint32_t LIM = 1000000;

int main()
{
    uint32_t k;
    scanf("%u", &k);
    static uint32_t R[MAX];
    R[0] = 1;
    for(uint32_t h = 1; h < MAX; h++)
    {
        if(h == k)
            continue;
        uint32_t s = 0;
        for(uint32_t i = 0; i < h; i++)
        {
            s += R[i];
            s %= LIM;
        }
        for(uint32_t i = h; i < MAX; i++)
        {
            R[i] = (s + LIM - (h > k ? R[i-k] : 0)) % LIM;
            s += R[i] + LIM - R[i-h];
            s %= LIM;
        }
    }
    uint32_t t;
    scanf("%u", &t);
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint32_t h;
        scanf("%u", &h);
        printf("%u\n", R[h]);
    }
}
