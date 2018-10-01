#pragma once

#include <cmath>
#include <cstdint>
using std::uint32_t;

// Constants: pi, phi
const long double A_PI = acos(-1.0L);
const long double PHI = (1 + sqrt(5)) / 2;

// Golden section method
// Works on functions with exactly one extremum (bitonic functions)
double function_minimum(double(*F)(double), double lo, double hi,
                        uint32_t iterations)
{
    double a = lo, b = hi, c = b - (b-a)/PHI, d = a + (b-a)/PHI;
    for(uint32_t k = 0; k < iterations; k++)
    {
        if(F(c) < F(d))
            b = d;
        else
            a = c;
        c = b - (b-a)/PHI;
        d = a + (b-a)/PHI;
    }
    return (a + b) / 2;
}
double function_maximum(double(*F)(double), double lo, double hi,
                        uint32_t iterations)
{
    double a = lo, b = hi, c = b - (b-a)/PHI, d = a + (b-a)/PHI;
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
