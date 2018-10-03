// LCA and jump pointers

// Last revision: 2017/2018

#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include <utility>

using std::uint32_t; using std::size_t;
using std::array;
using std::swap;

template<size_t JUMP_POINTERS, size_t MAX>
void do_jump_pointers_for(array<array<uint32_t, JUMP_POINTERS>, MAX>& J, uint32_t v)
{
    for(uint32_t i = 1; i < JUMP_POINTERS; i++)
    {
        uint32_t x = J[v][i-1];
        if(x == -1u) break;
        J[v][i] = J[x][i-1];
    }
}

template<size_t JUMP_POINTERS, size_t MAX>
uint32_t lca(const array<array<uint32_t, JUMP_POINTERS>, MAX>& J,
             const array<uint32_t, MAX>& D,
             uint32_t u, uint32_t v)
{
    if(D[u] < D[v])
        swap(u, v);
    for(uint32_t i = JUMP_POINTERS; i --> 0;)
        if(J[u][i] != -1u and D[J[u][i]] >= D[v])
            u = J[u][i];
    if(u == v)
        return u;
    for(uint32_t i = JUMP_POINTERS; i --> 0;)
    {
        if(J[u][i] != J[v][i] and J[u][i] != -1u)
            u = J[u][i], v = J[v][i];
    }
    return J[u][0];
}
