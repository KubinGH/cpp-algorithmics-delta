#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

const size_t LIM = 1000000033;
const size_t MAX = 1024;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    if(n == 1)
    {
        putchar('1');
        return 0;
    }
    bitset<MAX> P;
    P.set(); P[0] = false, P[1] = false;
    uint32_t amax = min(MAX-1, n);
    for(uint32_t i = 4; i <= amax; i += 2)
        P[i] = false;
    uint64_t r = 31 - __builtin_clz(n);
    for(uint32_t i = 3; i <= amax; i += 2)
    {
        if(not P[i])
            continue;
        for(uint32_t x = i*i; x <= amax; x += i)
            P[x] = false;
        uint64_t c = 0;
        for(uint32_t x = i; x <= n; x *= i)
            c++;
        if(c == 1)
            break;
        r *= c; r %= LIM;
    }
    printf("%u", (uint32_t)r);
}
