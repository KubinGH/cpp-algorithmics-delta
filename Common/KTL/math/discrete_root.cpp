// Discrete root
// - a number x, such that x^k ≡ a (mod m)
// returns a solution x and the generator data
// generator ^ (initial + i * period) for integer i are solutions
// This algorithm has the same requirements as the primitive root
// (m = 1, 2, 4, or p^k / 2p^k for p > 2)
// Note: because the root doesn't have to be coprime to m,
// the algorithm may not be able to find it, since it assumes
// the solution is coprime to m (generator powers are coprime)
// Complexity: primitive root + discrete logarithm

#pragma once

#include <algorithm>
#include "egcd.cpp"
#include "primitive_root.cpp"
#include "discrete_logarithm.cpp"

using std::__gcd;

template<typename T>
struct discrete_root_result { T solution, generator, initial, period; };

template<typename T>
discrete_root_result<T> discrete_root(T a, T k, T m)
{
    KTL_DEBUG_ASSERT(m != 0);
    mod_multiplies<T> Zm(m);
    auto g = primitive_root(m);
    if(g == -1u) return {};
    auto y = discrete_logarithm(power(g, k, Zm), a, m);
    if(y == -1u) return {};
    auto t = totient_from_factorization(m);
    return {power(g, y, Zm), g, y, Zm(t, egcd(__gcd(k, t), m).x)};
}
