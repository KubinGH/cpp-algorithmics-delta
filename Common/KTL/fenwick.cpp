#pragma once

#include <cstddef>
using std::size_t;

// Fenwick tree. Calculates prefix sums and allows for point changes.
// Compact, 0-based implementation.
template<typename T>
constexpr inline T lsb(T x) { return x & (-x); }

template<typename T>
struct fenwick_tree
{
    size_t n;
    T* F;
    fenwick_tree(size_t _n) { n = _n+1; F = new T[n+1]; fill(F, F + (n+1), 0); }
    ~fenwick_tree() { delete[] F; }
    T get_prefix(size_t p) const // Sum in [0, p)
        { T r = 0; p++; while(p) r += F[p], p -= lsb(p); return r; }
    void delta(size_t p, T v)
        { p += 2; while(p <= n) F[p] += v, p += lsb(p); }

    T get(size_t a, size_t b) const // Get on interval [a, b]
        { return get_prefix(b+1) - get_prefix(a); }
    T get(size_t p) const // Get on point [p]
        { return get(p, p); }
    void set(size_t p, T v)
        { return delta(p, v - get(p)); }
};
