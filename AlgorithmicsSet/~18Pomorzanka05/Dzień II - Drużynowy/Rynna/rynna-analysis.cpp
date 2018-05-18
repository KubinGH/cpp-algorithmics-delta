#include <bits/stdc++.h>

using namespace std;

const double PHI = (1 + sqrt(5)) / 2;

template<typename T>
T function_maximum(T(*F)(T), T lo, T hi,
                   uint32_t iterations)
{
    T a = lo, b = hi, c = b - (b-a)/PHI, d = a + (b-a)/PHI;
    for(uint32_t k = 0; k < iterations; k++)
    {
        if(F(c) > F(d))
            b = d;
        else
            a = c;
        c = b - (b-a)/PHI;
        d = a + (b-a)/PHI;
    }
    return (a + b) / 2;
}

double f(double x)
{
    return (sin(x) + 1) * cos(x);
}

int main()
{
    cout << fixed << setprecision(20);
    cout << f(function_maximum<double>(f, 0, acos(-1)/2, 1e5));
}
