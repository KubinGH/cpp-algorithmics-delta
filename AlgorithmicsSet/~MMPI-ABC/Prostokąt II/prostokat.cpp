#include <bits/stdc++.h>

using namespace std;

const uint64_t LIM = 1e9 + 9;

int main()
{
    uint64_t a, b, k;
    cin >> a >> b >> k;
    if(b < a) swap(a, b);
    uint64_t f = k * (k + 1) / 2;
    uint64_t o = (f + b - a) % 2;
    if(o) b--;
    if(a + f <= b)
        a += f;
    else
    {
        uint64_t x = (f + b - a) / 2;
        a += x;
        b += f - x;
    }
    cout << ((a % LIM) * ((b + o) % LIM)) % LIM;
}
