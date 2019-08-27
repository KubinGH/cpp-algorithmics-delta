// Fenwick tree. Calculates prefix sums and allows for point changes.
// Compact, 0-based implementation (albeit internals are 1-based)
// lower_bound based on https://codeforces.com/blog/entry/61364. Requires all implicit elements to be positive.
// p -= fenwicks::lsb(p)  <=>  p &= p - 1
// p += fenwicks::lsb(p)  <=>  p |= p - 1, p++
// (the first has proven to be visibly faster)

// Last revision: December 2018

#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>

using std::size_t;
using std::vector;
using std::__lg;

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    fenwick_tree(size_t _n) : n(_n), F(n+1, 0) {}

    static constexpr inline size_t lsb(size_t x) { return x & -x; }
    T get_prefix(size_t p) const
    {
        T r = 0;
        while(p)
            r += F[p], p -= lsb(p);
        return r;
    }
    void delta(size_t p, T v)
    {
        p++;
        while(p <= n)
            F[p] += v, p += lsb(p);
    }

    T get(size_t a, size_t b) const
        { return get_prefix(b+1) - get_prefix(a); }
    T get(size_t p) const
        { return get(p, p); }
    void set(size_t p, T v)
        { return delta(p, v - get(p)); }

    size_t lower_bound(T v)
    {
        T s = 0; size_t p = 0;
        for(size_t i = __lg(n)+1, q = (1u << __lg(n)); i --> 0; q /= 2)
            if(p + q <= n and s + F[p + q] < v)
                s += F[p + q], p += q;
        return p;
    }
};
