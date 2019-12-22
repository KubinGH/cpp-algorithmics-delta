// Finding the discrete logarithm.
// x such that a^x ≡ b (mod m) for given a, b, m.
// Returns the minimal one found, unless `any = true`.
// If no solutions are found, returns the max value for the type.
// Used transformation: a^ik ≡ b * a^j (mod m) for i, j ≤ k, such that x = ik - j
// Contains modifications that allow the routine to solve cases when gcd(a, m) ≠ 1.
//  (namely the shift, fix variables). Hint: ax ≡ ay (mod m) <=> x ≡ y (mod m/gcd(a, m))
// Complexity: O(sqrt(m))

// Last revision: April 2019

#pragma once

#include <unordered_map>
#include <algorithm>
#include <limits>
#include <cmath>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/numeric>
#include "mod_multiplies.cpp"
#include "../ktl_debug_mode.cpp"

using namespace std;
using __gnu_cxx::power;
using __gnu_pbds::gp_hash_table;
using std::ceil; using std::sqrt;
using std::__gcd;

template<typename T>
T discrete_logarithm(T a, T b, T m)
{
    KTL_DEBUG_ASSERT(m != 0);
    a %= m; b %= m;
    if(b == 1)
        return 0;

    T shift = 0, fix = 1;
    for(T g = __gcd(a, m); g != 1; g = __gcd(a, m))
    {
        if(b % g) return numeric_limits<T>::max();
        m /= g; b /= g;
        fix = mod_mul(fix, a / g, m);
        shift++;
        if(b == fix) return shift;
    }

    a %= m;

    T k = ceil(sqrt(m));

    gp_hash_table<T, T> rhs;
    T q = b;
    for(T j = 0; j < k; j++, q = mod_mul(q, a, m))
        rhs[q] = j;

    T w = power(a, k, mod_multiplies<T>(m));
    T p = mod_mul(w, fix, m);
    for(T i = 1; i <= k; i++, p = mod_mul(p, w, m))
        if(rhs.find(p) != rhs.end())
            return i * k - rhs[p] + shift;

    return numeric_limits<T>::max();
}
