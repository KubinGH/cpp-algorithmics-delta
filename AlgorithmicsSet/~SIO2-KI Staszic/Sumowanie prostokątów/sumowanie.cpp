#include <bits/stdc++.h>

using namespace std;

const size_t PREALLOC_COUNT = 1<<24;

struct treenode_t
{
    uint32_t value, to_add;
    size_t tbegin, tend;
    treenode_t *left, *right;
    treenode_t() : left(nullptr), right(nullptr) {}
    treenode_t* alloc_node()
    {
        static treenode_t prealloc[PREALLOC_COUNT];
        static size_t i = 0;
        if(i < PREALLOC_COUNT)
        {
            i++;
            return prealloc + i-1;
        }
        else
            return new treenode_t;
    }
    void create_left()
    {
        left = alloc_node();
        left->tbegin = tbegin; left->tend = (tbegin+tend)/2;
        left->value = 0; left->to_add = 0;
    }
    void create_right()
    {
        right = alloc_node();
        right->tbegin = (tbegin+tend)/2+1; right->tend = tend;
        right->value = 0; right->to_add = 0;
    }
    void pull()
    {
        if(to_add)
        {
            value += (tend - tbegin + 1) * to_add;
            if(tbegin < tend)
            {
                if(left == nullptr)
                    create_left();
                if(right == nullptr)
                    create_right();
                left ->to_add += to_add;
                right->to_add += to_add;
            }
            to_add = 0;
        }
    }
    void add_interval(uint32_t sbegin, uint32_t send, uint32_t addvalue)
    {
        pull();
        if(send < tbegin or tend < sbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_add += addvalue;
            pull();
        }
        else
        {
            pull();
            if(left == nullptr)
                create_left();
            left->add_interval(sbegin, send, addvalue);
            if(right == nullptr)
                create_right();
            right->add_interval(sbegin, send, addvalue);
            value = left->value + right->value;
        }
    }
    uint32_t get(uint32_t sbegin, uint32_t send)
    {
        if(send < tbegin or tend < sbegin)
            return 0;
        pull();
        if(sbegin <= tbegin and tend <= send)
            return value;
        else
        {
            if(left == nullptr)
                create_left();
            if(right == nullptr)
                create_right();
            return left->get(sbegin, send) + right->get(sbegin, send);
        }
    }
};

struct segment_tree
{
    treenode_t root;
    segment_tree() : segment_tree(0, 1u << 30) {}
    segment_tree(size_t abegin, size_t aend)
    {
        root.tbegin = abegin; root.tend = aend;
        root.value = 0; root.to_add = 0;
    }
    void add_interval(uint32_t sbegin, uint32_t send, uint32_t addvalue)
        { root.add_interval(sbegin, send, addvalue); }
    uint32_t get(uint32_t sbegin, uint32_t send)
        { return root.get(sbegin, send); }
};



int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    static segment_tree trees[1<<20];
    for(uint32_t i = 0; i < q; i++)
    {
        uint32_t p, a, b, c, d, v;
        cin >> p >> a >> b >> c >> d;
        if(p == 1)
        {
            cin >> v;
            for(uint32_t y = c; y <= d; y++)
                trees[y].add_interval(a, b, v);
        }
        else
        {
            uint32_t r = 0;
            for(uint32_t y = c; y <= d; y++)
                r += trees[y].get(a, b);
            cout << r << "\n";
        }
    }
}
