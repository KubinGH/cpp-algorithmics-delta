#include <bits/stdc++.h>

using namespace std;

long double a5, a4, a3, a2, a1, a0;

long double W(long double x)
{
    return a0 + x*(a1 + x*(a2 + x*(a3 + x*(a4 + x*a5))));
}

short sgn(long double n)
{
    return n < 0 ? -1 : 1;
}

int main()
{
    cin >> a5 >> a4 >> a3 >> a2 >> a1 >> a0;
    long double lo = -1000, hi = 1000;
    while(abs(W((lo+hi)/2)) > 0.000001)
    {
        long double x = (lo+hi)/2;
        if(sgn(W(lo)) != sgn(W(x)))
            hi = x;
        else
            lo = x;
    }
    cout << fixed << setprecision(6) << (lo+hi)/2;
}
