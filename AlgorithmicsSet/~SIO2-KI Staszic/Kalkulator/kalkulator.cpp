#include <bits/stdc++.h>

using namespace std;

int64_t fast_pow(int64_t b, int64_t n, int64_t mod)
{
    int64_t r = 1;
    while(n)
    {
        if(n % 2)
            r = (r * b) % mod;
        b = (b * b) % mod;
        n /= 2;
    }
    return r;
}

void lim(int64_t& n, int64_t p)
{
    while(n < 0) n += p;
    if(n >= p) n %= p;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int64_t p;
    cin >> p;
    int64_t n = 0;
    char op; int64_t v;
    while(cin >> op >> v)
    {
        lim(v, p);
        switch(op)
        {
            case '+':
                n += v;
                break;
            case '-':
                n -= v;
                break;
            case '*':
                n *= v;
                break;
            case '/':
                n *= fast_pow(v, p - 2, p);
                break;
        }
        lim(n, p);
    }
    cout << n;
}
