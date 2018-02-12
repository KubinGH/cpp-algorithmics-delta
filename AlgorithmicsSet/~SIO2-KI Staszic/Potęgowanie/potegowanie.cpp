#include <bits/stdc++.h>

using namespace std;

uint64_t a, m;

uint64_t modmul(uint64_t x, uint64_t y)
{
    if(x <= 1000000000 and y <= 1000000000)
        return ((x%m) * (y%m)) % m;
    if(x < y) swap(x, y);
    uint64_t r = 0;
    x = x % m;
    while(y)
    {
        if(y & 1)
            r = (r + x) % m;
        x = (x << 1) % m;
        y >>= 1;
    }
    return r % m;
}

uint64_t modpow(uint64_t b)
{
    uint64_t t;
    if(b == 0)
        return 1;
    else if(b == 1)
        return a;
    else if(not (b % 2))
    {
        t = modpow(b / 2) % m;
        return modmul(t, t);
    }
    else
        return modmul(modpow(b - 1), a);
}

int main()
{
    uint64_t b;
    cin >> a >> b >> m;
    a %= m;
    cout << modpow(b) << endl;
}
