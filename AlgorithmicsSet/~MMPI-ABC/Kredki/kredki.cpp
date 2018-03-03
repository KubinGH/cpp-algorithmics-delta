#include <bits/stdc++.h>

using namespace std;

const size_t LIM = 1e9 + 9;

uint64_t fast_pow(uint64_t b, uint64_t n, uint64_t mod)
{
    uint64_t r = 1;
    while(n)
    {
        if(n % 2)
            r *= b; r %= mod;
        b *= b; b %= mod;
        n /= 2;
    }
    return r % mod;
}

int main()
{
    uint64_t b, c;
    cin >> b >> c;
    if(b > c) swap(b, c);
    uint64_t r = 1;
    for(uint64_t i = c + 1; i <= b + c; i++)
        r *= i, r %= LIM;
    for(uint64_t i = 1; i <= b; i++)
        r *= fast_pow(i, LIM - 2, LIM), r %= LIM;
    cout << r;
}
