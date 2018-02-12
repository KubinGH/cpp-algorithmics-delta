#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint64_t;

const uint64_t MOD = 1000000033;

uint64_t modpow(uint64_t a, uint64_t b)
{
    uint64_t r = 1;
    while(b > 0) {

        if(b % 2 == 1) {
            r = (r*a) % MOD;
        }
        a = (a * a) % MOD;
        b = b / 2;
    }
    return r % MOD;
}

int main()
{
    uint64_t n;
    cin >> n;
    uint64_t c = ceil(log2(n));
    if(__builtin_popcountll(n) == 1) c++;
    uint64_t r = 0;
    for(uint64_t i = 0; i < c; i++)
    {
        r *= 2;
        r++;
    }
    r %= MOD;
    cout << (r * modpow(2, n - c)) % MOD;
}
