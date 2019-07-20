// Primitive root (aka generator)
// such a number g, that for every a, the exist k such that g^k ≡ a (mod m) for given m.
// Generators exist for the following:
// * 1, 2, 4
// * p^k and 2 p^k for prime p > 2 and integer k.
// This should be checked for separately.
// The number of tries to obtain the primitive root is limited to avoid infinite loops.
// Complexity: O(F(n) + t * log^2 n),
//             where F is the time taken to factorize an integer, and t is the number of tries.
//             The number of tries is low on average.
// Last revision: April 2019

#include <limits>
#include <random>
#include <cstddef>
#include <algorithm>
#include "factorization.cpp"
#include "mod_multiplies.cpp"
#include "../ktl_debug_mode.cpp"

using std::size_t;
using std::__gcd;
using std::mt19937; using std::random_device; using std::uniform_int_distribution;
using std::numeric_limits;

const size_t PRIMITIVE_ROOT_TRIES = 1024;

template<typename T>
T totient_from_factorization(T n)
{
    auto F = factorize_int(n);
    F.erase(unique(F.begin(), F.end()), F.end());
    T t = n;
    for(auto p : F)
        t /= p, t *= p - 1;
    return t;
}

template<typename T>
T primitive_root(T m)
{
    KTL_DEBUG_ASSERT(m != 0);
    if(m == 1) return 0;

    T t = totient_from_factorization(m);
    auto F = factorize_int(t);
    F.erase(unique(F.begin(), F.end()), F.end());

    mod_multiplies<T> M(m);

    static mt19937 gen(random_device{}());
    for(size_t i = 0; i < PRIMITIVE_ROOT_TRIES; i++)
    {
        T g = i < 10 ? i+1 : uniform_int_distribution<T>{1, m - 1}(gen);

        if(__gcd(g, m) != 1)
            continue;

        bool ok = true;

        for(auto p : F)
            if(power(g, t / p, M) == 1)
                { ok = false; break; }

        if(ok)
            return g;
    }
    return numeric_limits<T>::max();
}
