// Two-dimensional Fenwick tree

// Last revision: December 2018

#pragma once

#include <cstddef>
#include <vector>
#include "fenwick.cpp"
using std::size_t;
using std::vector;

template<typename T>
struct fenwick_tree_2d
{
    size_t w, h;
    vector<fenwick_tree<T>> G;
    fenwick_tree_2d(size_t _w, size_t _h) : w(_w), h(_h), G(h+1, _w) {}

    T get_prefix(size_t x, size_t y) const // Sum in [0, x) . [0, y)
        { T r = 0; while(y) r += G[y].get_prefix(x), y &= y - 1; return r; }
    void delta(size_t x, size_t y, T v)
        { y++; while(y <= h) G[y].delta(x, v), y |= y - 1, y++; }

    T get(size_t x1, size_t y1, size_t x2, size_t y2) const
    {
        return get_prefix(x2+1, y2+1) + get_prefix(x1, y1)
             - get_prefix(x2+1, y1) - get_prefix(x1, y2+1);
    }
    T get(size_t x, size_t y)
        { return get(x, y, x, y); }
};
