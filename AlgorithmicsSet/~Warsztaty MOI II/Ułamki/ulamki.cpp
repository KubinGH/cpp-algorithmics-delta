#include <bits/stdc++.h>

using namespace std;

uint64_t gcd(uint64_t a, uint64_t b)
{
    return __gcd(a, b);
}
uint64_t lcm(uint64_t a, uint64_t b)
{
    return a / gcd(a, b) * b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    for(uint32_t i = 0; i < q; i++)
    {
        uint64_t a, b, c, d, x, y, g;
        cin >> a >> b >> c >> d;
        x = a*d + b*c;
        y = b*d;
        g = gcd(x, y);
        x /= g; y /= g;
        cout << x << ' ' << y << '\n';
    }
}
