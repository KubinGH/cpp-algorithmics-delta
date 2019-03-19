// Chinese Remainder Theorem
// Solves systems of congruences. Works for non-coprime moduli.
// Provide congruences as pairs [x |= first (mod second)],
// returns {0, 0} if there is no solution.
// Last Revision: March 2019

#pragma once

#include <vector>
#include <utility>
#include "egcd.cpp"

int64_t umod(int64_t a, int64_t b) { return (a%b + b) % b; }

pair<int64_t, int64_t> crt(vector<pair<int64_t, int64_t>> congo)
{
    while(congo.size() > 1)
    {
        int64_t a1, n1, a2, n2;
        tie(a1, n1) = congo.back(); congo.pop_back();
        tie(a2, n2) = congo.back(); congo.pop_back();

        auto r = egcd(n1, n2);
        auto m1 = r.x, m2 = r.y;
        int64_t g = r.d, m = n1 / r.d * n2;
        if(umod(a1 - a2, g))
            return {0, 0};
        int64_t x = (a1*m2*n2 + a2*m1*n1) / g;

        congo.emplace_back(umod(x, m), m);
    }
    return congo.back();
}
