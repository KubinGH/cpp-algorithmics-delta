// Utility for the flow algorithms.

#pragma once

#include <vector>
#include <cstdint>

using namespace std;

namespace flow
{
    using capacity_t = uint32_t;

    struct edge
    {
        size_t v; capacity_t c;
        edge(size_t _v, capacity_t _c) : v(_v), c(_c) {}
    };
    struct bnd_edge
    {
        size_t u, v; capacity_t c; size_t rev_i;
        bnd_edge(size_t _u, size_t _v, capacity_t _c, size_t _rev_i)
            : u(_u), v(_v), c(_c), rev_i(_rev_i) {}
    };

    using graph = vector<vector<edge>>;
    using bnd_graph = vector<vector<bnd_edge>>;
}
