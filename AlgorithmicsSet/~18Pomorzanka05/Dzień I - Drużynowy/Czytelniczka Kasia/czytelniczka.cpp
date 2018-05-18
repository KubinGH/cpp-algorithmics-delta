#include <bits/stdc++.h>

using namespace std;

int main()
{
    uint32_t n;
    cin >> n;
    uint32_t k = 1, dr = 0;
    while(k != 0)
    {
        cin >> k;
        dr += k;
    }
    uint32_t g = __gcd(dr, n);
    dr /= g; n /= g;
    cout << dr << "/" << n;
}
