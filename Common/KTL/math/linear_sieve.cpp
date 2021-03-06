// Linear sieve for finding prime numbers
// also computes the minimum prime factor array (M), which can be used for factorization
// Can be extended to compute multiplicative functions
// Complexity: O(n)
// Last revision: March 2019

#pragma once

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>
#include "../ktl_debug_mode.cpp"

using std::size_t;
using std::__lg;
using std::pair; using std::vector;

pair<vector<size_t>, vector<size_t>> linear_sieve_dual(size_t n)
{
    KTL_DEBUG_ASSERT(n > 0);
    vector<size_t> P, M(n);
    P.reserve(2 * n / __lg(n));
    for(size_t x = 2; x < n; x++)
    {
        if(not M[x])
            M[x] = x, P.push_back(x);
        for(size_t i = 0; i < P.size() and x * P[i] < n and P[i] <= M[x]; i++)
            M[x * P[i]] = P[i];
    }
    return {P, M};
}

vector<size_t> linear_sieve(size_t n)
{
    return linear_sieve_dual(n).first;
}
