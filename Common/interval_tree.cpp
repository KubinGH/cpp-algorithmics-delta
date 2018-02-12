#include <bits/stdc++.h>

using namespace std;

uint64_t pow2_ge(uint64_t n)
{
    uint64_t r = 1;
    while(r < n) r *= 2;
    return r;
}

template<size_t SIZE>
struct interval_tree
{
    static const size_t TSIZE = 4 * SIZE;
    const uint64_t root = 1;
    size_t tsize;
    array<uint64_t, TSIZE> values;
    interval_tree(size_t least_size = SIZE)
    {
        tsize = pow2_ge(least_size) * 2;
        for(uint64_t i = 0; i < values.size(); i++)
            values[i+1] = 0;
    }
    inline uint64_t parent(uint64_t node)
    {
        return node / 2;
    }
    inline uint64_t child_left(uint64_t node)
    {
        return node * 2;
    }
    inline uint64_t child_right(uint64_t node)
    {
        return node * 2 + 1;
    }
    inline uint64_t leaf(uint64_t i = 0)
    {
        return tsize / 2 + i;
    }
    void set_value(uint64_t node, uint64_t value)
    {
        values[node] = value;
        while(node != root)
        {
            node = parent(node);
            values[node] = max(values[child_left(node)], values[child_right(node)]);
        }
    }
    uint64_t find_best(uint64_t node, uint64_t tbegin, uint64_t tend, uint64_t sbegin, uint64_t send)
    {
        if(send < tbegin or tend < sbegin) // disjoint
        {
            return 0;
        }
        else if(sbegin <= tbegin and tend <= send) // entire
        {
            return values[node];
        }
        else // part
        {
            uint64_t left = find_best(child_left(node), tbegin, (tbegin+tend)/2, sbegin, send);
            uint64_t right = find_best(child_right(node), (tbegin+tend)/2+1, tend, sbegin, send);
            return max(left, right);
        }
    }
    uint64_t find_best(uint64_t sbegin, uint64_t send)
    {
        return find_best(root, 0, tsize / 2 - 1, sbegin, send);
    }
    uint64_t find_best()
    {
        return find_best(root, 0, tsize / 2 - 1, 0, tsize / 2 - 1);
    }
};