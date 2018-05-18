#include <bits/stdc++.h>

using namespace std;

const uint64_t LIM = 1e9+7;

uint64_t fast_pow(uint64_t a, uint64_t b)
{
    uint64_t r = 1;
    while(b)
    {
        if(b % 2 == 1)
            r *= a, r %= LIM;
        b /= 2;
        a *= a; a %= LIM;
    }
    return r;
}

int main()
{
    uint64_t n;
    cin >> n;
    cout << (4 * fast_pow(3, n - 1)) % LIM;
}
