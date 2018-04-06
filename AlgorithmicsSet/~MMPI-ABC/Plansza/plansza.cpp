#include <bits/stdc++.h>

using namespace std;

const uint64_t LIM = 1e9 + 7;

uint64_t fast_pow(uint64_t b, uint64_t n)
{
    uint64_t r = 1;
    while(n)
    {
        if(n % 2 == 0)
            b *= b, b %= LIM, n /= 2;
        r *= b; r %= LIM;
        n--;
    }
    return r;
}

int main()
{
    uint64_t n, m;
    cin >> n >> m;
    uint64_t k = fast_pow(2, n);
    cout << (k * fast_pow(k - 1, m - 1)) % LIM;
}
