#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int uint64_t;

int main()
{
    uint64_t C, W;
    cin >> C >> W;
    // C * 10^x + k = W(10k + C)
    // => k = C(10^x - W) / (10W - 1)
    // x = ?, (10W - 1) | C(10^x - W)
    uint64_t x = 0, d = 1;
    while(d < W) d *= 10, x++;
    uint64_t p = (10*W - 1);
    d %= p;
    while((C * (d - W)) % p != 0)
    {
        x++; d *= 10; d %= p;
    }
    cout << x + 1;
}
