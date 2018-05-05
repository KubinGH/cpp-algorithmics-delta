#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

const size_t PRIME_LIM = 2e6;

int main()
{
    uint32_t n;
    scanf("%u", &n);
    static bool is_prime[PRIME_LIM];
    fill(is_prime, is_prime + PRIME_LIM, true);
    is_prime[0] = is_prime[1] = false;
    for(uint32_t p = 2; p < PRIME_LIM; p++)
    {
        if(not is_prime[p])
            continue;
        if(p < ((1u << 16) - 16)) for(uint32_t x = p*p; x < PRIME_LIM; x += p)
            is_prime[x] = false;
    }
    for(uint32_t i = 0; i < n; i++)
    {
        uint64_t x;
        scanf("%llu", &x);
        uint64_t r = floor(sqrt(x));
        if(r*r == x and is_prime[r])
            printf("TAK\n");
        else
            printf("NIE\n");
    }
}
