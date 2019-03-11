// Fenwick tree. Calculates prefix sums and allows for point changes.
// Compact, 0-based implementation (albeit internals are 1-based)
// lower_bound based on https://codeforces.com/blog/entry/61364
// p -= fenwicks::lsb(p)  <=>  p &= p - 1
// p += fenwicks::lsb(p)  <=>  p |= p - 1, p++
// (both have been proven to be slightly faster)

// Last revision: December 2018

#pragma once

#include <cstddef>
#include <vector>
using std::size_t;
using std::vector;


namespace fenwicks
{
    template<typename Tp>
    static constexpr inline Tp lsb(Tp x) { return x & (-x); }
}

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    size_t lg, q_lg;
    fenwick_tree(size_t _n) : n(_n), F(n+1, 0), lg(32 - __builtin_clz(n)), q_lg(1 << (lg-1)) {}
    T get_prefix(size_t p) const // Sum in [0, p)
        { T r = 0; while(p) r += F[p], p &= p - 1; return r; }
    void delta(size_t p, T v)
        { p++; while(p <= n) F[p] += v, p |= p - 1, p++; }

    T get(size_t a, size_t b) const // Get on interval [a, b]
        { return get_prefix(b+1) - get_prefix(a); }
    T get(size_t p) const // Get on point [p]
        { return get(p, p); }
    void set(size_t p, T v)
        { return delta(p, v - get(p)); }

    size_t lower_bound(T v)
    {
        T s = 0; size_t p = 0;
        for(size_t i = lg, q = q_lg; i --> 0; q /= 2)
            if(p + q < n and s + F[p + q] < v)
                s += F[p + q], p += q;
        return p;
    }
    size_t find_by_order(size_t i) { return lower_bound(i+1) - 1; }
};
