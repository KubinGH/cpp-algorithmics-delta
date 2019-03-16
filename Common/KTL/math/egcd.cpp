// Extended Euclidean algorithm
// Finds solutions to ax + by = p*gcd(a, b)
// Bezout's identity:
//   x' = x + k (b / gcd(a, b))
//   y' = y - k (a / gcd(a, b))
//   ax' + by' = p*gcd(a, b)

// Last revision: March 2019

#pragma once

struct egcd_res { int64_t d, x, y; };
egcd_res egcd(int64_t a, int64_t b)
{
    if(a == 0)
        return {b, 0, 1};
    auto r = egcd(b % a, a);
    return {r.d, r.y - (b/a)*r.x, r.x};
}
