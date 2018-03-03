#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 100000;

uint32_t fast_pow(uint32_t b, uint32_t n, uint32_t mod)
{
    uint32_t r = 1;
    while(n)
    {
        if(n % 2)
            r *= b, r %= mod;
        b *= b; b %= mod;
        n /= 2;
    }
    return r % mod;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, p, m;
    cin >> n >> p >> m;
    for(uint32_t k = 1; k <= n; k++)
    {
        static array<bool, MAX> A;
        fill(A.begin(), A.begin() + m, false);
        uint32_t x = k;
        uint32_t a = 0;
        //cerr << k << ": " << k << " ";
        while(not A[x])
        {
            a++; A[x] = true;
            uint32_t y = x;
            x = 0;
            while(y)
            {
                x += fast_pow(y % 10, p, m);
                y /= 10;
            }
            x %= m;
            //cerr << x << ":" << A[x] << " ";
        }
        //cerr << "(" << x << ":" << A[x] << ")" << endl;
        cout << a << " ";
        //cerr << endl;
    }
}
