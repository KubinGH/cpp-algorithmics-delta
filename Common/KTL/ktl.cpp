#include <bits/stdc++.h>

// Kubin's Template Library (tm)

using namespace std;

namespace ktl
{
    #include "general/binary_search.cpp"
    #include "general/number.cpp"

    #include "geometry/convex_hull.cpp"
    #include "geometry/vec2d.cpp"

    #include "graph/kosaraju.cpp"
    #include "graph/lca.cpp"

    #include "math/extended_euclidean.cpp"
    #include "math/golden_section.cpp"
    #include "math/matrix.cpp"
    #include "math/primemath.cpp"

    #include "structures/disjoint_set.cpp"
    #include "structures/fenwick.cpp"
    #include "structures/heap.cpp"
    #include "structures/randomized_heap.cpp"
    #include "structures/segment_tree.cpp"
    #include "structures/sparse_table.cpp"
    #include "structures/value_scaler.cpp"
    #include "structures/wavelet_tree.cpp"

    #include "text/kmr.cpp"
    #include "text/manacher.cpp"
    #include "text/prefixoprefixes.cpp"
    #include "text/prefixosuffixes.cpp"
    #include "text/rolling_hash.cpp"

    #include "util/chronohelper.cpp"
    #include "util/fastio.cpp"
    #include "util/randutil.cpp"

    #include "util/zeus/socket.cpp"
}

int main()
{
    ktl::fenwick_tree<int> F(10);
    for(uint32_t i = 0; i < 10; i++)
        F.delta(i, i+1);
    for(uint32_t i = 0; i < 10; i++)
        cout << F.get(0, i) << " ";
    cout << endl;
}
