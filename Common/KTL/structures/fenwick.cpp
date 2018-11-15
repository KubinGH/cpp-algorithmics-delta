// Fenwick tree. Calculates prefix sums and allows for point changes.
// Compact, 0-based implementation.
// lower_bound based on https://codeforces.com/blog/entry/61364

// Last revision: October 2018

#pragma once

#include <cstddef>
#include <vector>
using std::size_t;
using std::vector;

template<typename T>
constexpr inline T lsb(T x) { return x & (-x); }

template<typename T>
struct fenwick_tree
{
    size_t n;
    vector<T> F;
    fenwick_tree(size_t _n) : n(_n+1), F(n+1, 0) {}
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

    size_t lower_bound(T v)
    {
        // min p: get_prefix(p) >= v
        T s = 0; size_t p = 0;
        for(size_t i = (32 - __builtin_clz(n)); i --> 0; ) // \log2(n)/+1
        {
            if(p + (1u << i) < n and s + F[p + (1u << i)] < v)
                s += F[p + (1u << i)], p += 1u << i;
        }
        return p;
    }
    size_t find_by_order(size_t i) { return lower_bound(i+1) - 1; }
};

template<typename T>
struct fenwick_tree_2d
{
    size_t w, h;
    vector<fenwick_tree<T>> G;
    fenwick_tree_2d(size_t _w, size_t _h) : w(_w+1), h(_h+1), G(h+1, _w) {}

    T get_prefix(size_t x, size_t y) const // Sum in [0, x) . [0, y)
        { T r = 0; y++; while(y) r += G[y].get_prefix(x), y -= lsb(y); return r; }
    void delta(size_t x, size_t y, T v)
        { y += 2; while(y <= h) G[y].delta(x, v), y += lsb(y); }

    T get(size_t x1, size_t y1, size_t x2, size_t y2) const
    {
        return get_prefix(x2+1, y2+1) + get_prefix(x1, y1)
             - get_prefix(x2+1, y1) - get_prefix(x1, y2+1);
    }
    T get(size_t x, size_t y)
        { return get(x, y, x, y); }
};
