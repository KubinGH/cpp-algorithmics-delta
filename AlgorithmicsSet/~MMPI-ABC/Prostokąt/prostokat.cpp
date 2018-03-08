#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint64_t a, b; uint32_t k;
    cin >> a >> b >> k;
    if(a > b) swap(a, b);
    if(a < b)
    {
        uint32_t t = min(k, (uint32_t)(b - a));
        k -= t;
        a += t;
    }
    a += k / 2;
    b += (k + 1) / 2;
    cout << a * b;
}
