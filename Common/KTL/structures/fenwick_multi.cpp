// Multi-dimensional Fenwick tree with templates
// note that the ordering is different than in "fenwick.cpp", due to
// technical limitations: delta(v, p1, p2, ...) instead of delta(p, v).

// Last revision: December 2018

#pragma once

#include <cstddef>
#include <vector>
#include "fenwick.cpp"

using std::size_t;
using std::vector;

template<typename T, size_t DIM>
struct dfenwick_tree;

template<typename T>
struct dfenwick_tree<T, 1>
{
    fenwick_tree<T> F;
    dfenwick_tree(size_t n) : F(n) {}
    T get_prefix(size_t p) const { return F.get_prefix(p); }
    void delta(T v, size_t p) { return F.delta(p, v); }
};

template<typename T, size_t DIM>
struct dfenwick_tree
{
    size_t n;
    vector<dfenwick_tree<T, DIM - 1>> F;
    template<typename... Args>
    dfenwick_tree(size_t _n, Args... args) : n(_n), F(n+1, dfenwick_tree<T, DIM - 1>{args...}) {}

    template<typename... Args>
    T get_prefix(size_t p, Args... args) const
    {
        T r = 0;
        while(p)
            r += F[p].get_prefix(args...), p -= fenwick_tree<T>::lsb(p);
        return r;
    }

    template<typename... Args>
    void delta(T v, size_t p, Args... args)
    {
        p++;
        while(p <= n)
            F[p].delta(v, args...), p += fenwick_tree<T>::lsb(p);
    }
};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
