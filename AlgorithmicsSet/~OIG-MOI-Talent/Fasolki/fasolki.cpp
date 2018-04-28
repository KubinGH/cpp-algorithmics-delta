#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint64_t;
typedef unsigned int uint32_t;

const size_t MAX = 500000, TMAX = 20;
const uint64_t MOD = 1e9+9;

uint64_t fast_pow(uint64_t a, uint64_t b)
{
    uint64_t result = 1;
    while(b)
    {
        if(b % 2)
        {
            result *= a;
            result %= MOD;
        }
        b /= 2;
        a *= a; a %= MOD;
    }
    return result;
}

int main()
{
    uint32_t t;
    scanf("%u", &t);
    static uint64_t F[size_t(2e6+1)];
    F[0] = 1;
    for(uint64_t i = 1; i <= 2e6; i++)
        F[i] = (F[i-1] * i) % MOD;
    for(uint32_t ti = 0; ti < t; ti++)
    {
        uint64_t n, k;
        scanf("%llu %llu", &n, &k);
        printf("%llu\n", (((F[n+k-1] * fast_pow(F[k], MOD-2)) % MOD) * fast_pow(F[n-1], MOD-2)) % MOD);
    }
}
