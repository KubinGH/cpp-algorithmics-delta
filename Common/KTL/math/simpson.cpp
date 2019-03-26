// Integration by Simpson's formula.
// Last revision: March 2019
#pragma once

#include <cstdint>
#include <cmath>

using std::size_t;
using std::abs;

template<typename T, typename Function>
T simpson_integration(Function f, T a, T b, size_t n)
{
    T h = (b - a) / (2 * n);
    T s = f(a) + f(b);
    for(size_t i = 1; i < 2 * n; i++)
    {
        T x = a + h * i;
        s += f(x) * (i%2 ? 4 : 2);
    }
    return s * (h / 3);
}

template<typename T, typename Function>
T extended_simpson_integration(Function f, T a, T b, size_t n, T eps)
{
    T h = (b - a) / (2 * n);
    T s = f(a) + f(b);
    for(size_t i = 1; i < 2 * n; i++)
    {
        T x = a + h * i;
        s += f(x) * (i%2 ? 4 : 2);
    }
    auto left = simpson_integration(f, a, (a+b)/2, n),
        right = simpson_integration(f, (a+b)/2, b, n);
    auto result = s * (h / 3);
    if(abs((left + right) - result) > eps)
        return extended_simpson_integration(f, a, (a+b)/2, n, eps)
             + extended_simpson_integration(f, (a+b)/2, b, n, eps);
    else
        return result;
}
