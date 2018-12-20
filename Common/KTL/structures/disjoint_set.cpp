// Disjoint-set data structure (Find and Union)

// Last revision: December 2018

#pragma once

#include <cstddef>
#include <vector>
#include <algorithm>
using std::size_t; using std::vector;
using std::iota; using std::swap;

struct disjoint_set
{
    size_t n;
    vector<size_t> parent, nrank;
    disjoint_set(size_t _n) : n(_n)
    {
        parent.resize(n); nrank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    void unite(size_t u, size_t v)
    {
        if(nrank[v = find(v)] > nrank[u = find(u)])
            swap(u, v);
        parent[v] = u;
        if(nrank[u] == nrank[v])
            nrank[u]++;
    }
    size_t find(size_t u)
    {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
};
