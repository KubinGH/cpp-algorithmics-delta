#include <bits/stdc++.h>

using namespace std;

const uint64_t MOD = 1e9+33;

uint64_t F(uint32_t i)
{
    if(i == 0)
        return 1;
    else
        return i * F(i-1);
}

uint64_t pow(uint64_t a, uint64_t b)
{
    uint64_t r = 1;
    while(b)
    {
        if(b % 2)
            r *= a, r %= MOD;
        b /= 2; a *= a; a %= MOD;
    }
    return r;
}

int main()
{
    uint32_t a, b, n;
    cin >> a >> b >> n;
    uint32_t r_a = 0, r_b = 0;
    for(uint32_t i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if(c == '0')
            r_a++;
        else if(c == '1')
            r_b++;
    }
    if(a < r_a or b < r_b)
    {
        cout << -1;
        return 0;
    }
    uint32_t x = a - r_a, y = b - r_b;
    uint64_t r = 1;

    cout << r;
}
