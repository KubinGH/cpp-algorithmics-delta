// Disjoint-set data structure (Find and Union)

// Last revision: 2017

#pragma once

#include <cstddef>
#include <array>
using std::size_t; using std::array;

template<size_t N>
struct disjoint_set
{
    array<size_t, N> parent, nrank;
    disjoint_set(size_t init = N)
    {
        iota(parent.begin(), parent.begin() + init, 0);
    }
    void unite(size_t first_node, size_t second_node)
    {
        size_t first = find_root(first_node),
               second = find_root(second_node);
        if(nrank[second] > nrank[first])
        {
            parent[first] = second;
            nrank[second]++;
        }
        else
        {
            parent[second] = first;
            if(nrank[first] == nrank[second])
                nrank[first]++;
        }
    }
    size_t find_root(size_t node)
    {
        if(parent[node] == node)
            return node;
        parent[node] = find_root(parent[node]);
        return parent[node];
    }
};
