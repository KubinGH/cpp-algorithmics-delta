#pragma GCC optimize ("Ofast")
#pragma GCC target("tune=native")
#include <bits/stdc++.h>
#include <ext/numeric>

using namespace std;
using __gnu_cxx::power;

const uint64_t MOD = 1e9 + 7;

uint64_t get(int32_t x, int32_t y)
{
    int64_t s = max(abs(x), abs(y));
    uint64_t b = (2*s-1)*(2*s-1);
    if(x == s and y == -s)
        return uint64_t(2*s+1)*(2*s+1) % MOD;
    else if(x == s)
        return uint64_t(b + y + 1 + (s - 1)) % MOD;
    else if(y == s)
        return uint64_t(b + 2*s + (s-x)) % MOD;
    else if(x == -s)
        return uint64_t(b + 4*s + (s-y)) % MOD;
    else if(y == -s)
        return uint64_t(b + 6*s + (x+s)) % MOD;
    __builtin_unreachable();
}

inline int32_t cut(int32_t a, int32_t b, int32_t c, int32_t d)
{
    return max((b<d ? b : d) - (a>c ? a : c) + 1, 0);
}

#define COEFF1(a2,a3,a4) ((5*MOD + a4 + 3*a2 - 3*a3) % MOD)
#define COEFF2(a2,a3,a4) (3*(10*MOD + -a4 - 5*a2 + 4*a3) % MOD)
#define COEFF3(a2,a3,a4) ((30*MOD + 2*a4 + 18*a2 - 9*a3) % MOD)

uint64_t cubic(uint64_t a, uint64_t b, uint64_t c, uint64_t x)
{
    return (x*(x*(a*x%MOD + b)%MOD + c))%MOD;
}

uint64_t sigma(uint64_t a, uint64_t n)
{
    return (a*n + (n*(n-1)/2)) % MOD;
}

uint64_t rowd(int32_t x1, int32_t x2, int32_t y)
{
    if(x1 > x2)
        return 0;
    uint64_t t1, t2, t3;
    int32_t y1 = abs(y);
    if(x2 < -y1)
        t1 = get(-y1-1, y), t2 = get(-y1-2, y), t3 = get(-y1-3, y);
    else
        t1 = get(y1+1, y), t2 = get(y1+2, y), t3 = get(y1+3, y);
    uint64_t a2 = t1, a3 = (a2+t2)%MOD, a4 = (a3+t3)%MOD;
    uint64_t a = COEFF1(a2,a3,a4), b = COEFF2(a2,a3,a4), c = COEFF3(a2,a3,a4);
    if(x2 < -y1)
        return MOD + cubic(a, b, c, -y1-x1) - cubic(a, b, c, -y1-x2-1);
    else
        return MOD + cubic(a, b, c, x2-y1) - cubic(a, b, c, x1-y1-1);
}


uint64_t row(int32_t x1, int32_t x2, int32_t y)
{
    if(y >= 0)
    {
        return sigma(get(min(y, x2), y), cut(x1, x2, -y, y)) +
               (rowd(x1, min(x2, -y-1), y) + rowd(max(x1, y+1), x2, y))*166666668%MOD;
    }
    else
    {
        y = -y;
        return sigma(get(max(-y, x1), -y), cut(x1, x2, -y, y)) +
                (rowd(x1, min(x2, -y-1), -y) + rowd(max(x1, y+1), x2, -y))*166666668%MOD;
    }
}

uint64_t get(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    uint64_t r = 0;
    for(int32_t y = y1; y <= y2; y++)
        r += row(x1, x2, y);
    return r % MOD;
}

int main()
{
    uint32_t _, q;
    cin >> _ >> q;

    for(uint32_t i = 0; i < q; i++)
    {
        int64_t x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << get(x1, y1, x2, y2) << "\n";
    }
}
