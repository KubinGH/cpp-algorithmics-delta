// Extended Euclidean algorithm
// Finds solutions to ax + by = p*gcd(a, b)
// Bezout's identity:
//   x' = x + k (b / gcd(a, b))
//   y' = y - k (a / gcd(a, b))
//   ax' + by' = p*gcd(a, b)

// Last revision: 2017/2018

#pragma once

#include <algorithm>
#define gcd __gcd

template<typename T>
struct gcdext_result { T d, x, y; };

template<typename T>
gcdext_result<T> gcdext(T a, T b)
{
    if(a == 0)
        return {b, 0, 1};
    auto next = gcdext(b % a, a);
    return {next.d, next.y - (b/a)*next.x, next.x};
}

#undef gcd
