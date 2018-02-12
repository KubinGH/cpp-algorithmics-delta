#include <bits/stdc++.h>

#define TESTING
#define TEST_FILENAME "tests/testa4"
#include "testhelper.h"

using namespace std;

uint32_t pow2_ge(uint32_t n)
{
    uint32_t r = 1;
    while(r < n) r *= 2;
    return r;
}

// F - set new value to parent or do not replace best
//     if F(old_value, new_value)
template<size_t MAX_SIZE = 100000, typename FT = greater<uint32_t> >
struct interval_tree
{
    FT F;
    const uint32_t root = 1;
    const uint32_t inf = numeric_limits<uint32_t>::max();
    size_t tsize;
    array<uint32_t, MAX_SIZE+1> values;
    interval_tree(size_t least_size = MAX_SIZE, FT f = FT())
    {
        F = f;
        tsize = pow2_ge(least_size) * 2;
        for(uint32_t i = 0; i < values.size(); i++)
            values[i+1] = inf;
    }
    inline uint32_t parent(uint32_t node)
    {
        return node / 2;
    }
    inline uint32_t child_left(uint32_t node)
    {
        return node * 2;
    }
    inline uint32_t child_right(uint32_t node)
    {
        return node * 2 + 1;
    }
    inline uint32_t leaf(uint32_t i = 0)
    {
        return tsize / 2 + i;
    }
    void set_value(uint32_t node, uint32_t value)
    {
        values[node] = value;
        while(node != root)
        {
            node = parent(node);
            values[node] = value;
            if(F(values[node], values[child_left(node)]))
                values[node] = values[child_left(node)];
            if(F(values[node], values[child_right(node)]))
                values[node] = values[child_right(node)];
        }
    }
    // tbegin, tend - current node bounds; sbegin, send - searched bounds
    uint32_t find_best(uint32_t node, uint32_t tbegin, uint32_t tend, uint32_t sbegin, uint32_t send)
    {
        if(send < tbegin or tend < sbegin) // disjoint
        {
            return inf;
        }
        else if(sbegin <= tbegin and tend <= send) // entire
        {
            return values[node];
        }
        else // part
        {
            uint32_t left = find_best(child_left(node), tbegin, (tbegin+tend)/2, sbegin, send);
            uint32_t right = find_best(child_right(node), (tbegin+tend)/2+1, tend, sbegin, send);
            return F(left, right) ? right : left;
        }
    }
};

int main()
{
    INIT_TESTER;
    uint32_t plots;
    cin >> plots;
    static interval_tree<> tree(plots);
    for(uint32_t i = 0; i < plots; i++)
    {
        uint32_t current;
        cin >> current;
        tree.set_value(tree.leaf(i), current);
    }
    uint32_t operations;
    cin >> operations;
    for(uint32_t o = 0; o < operations; o++)
    {
        char operation;
        cin >> operation;
        if(operation == 'Z')
        {
            uint32_t i, value;
            cin >> i >> value; i--;
            tree.set_value(tree.leaf(i), value);
        }
        if(operation == 'M')
        {
            uint32_t sbegin, send;
            cin >> sbegin >> send; sbegin--; send--;
            cout << tree.find_best(tree.root, 0, tree.tsize/2 - 1, sbegin, send) << " ";
        }
    }
    FINISH_TEST;
}
