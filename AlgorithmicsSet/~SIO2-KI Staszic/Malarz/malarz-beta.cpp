#include <bits/stdc++.h>

using namespace std;

const size_t PREALLOC_COUNT = 1 << 18;

struct treenode_t
{
    uint32_t value;
    bool to_flip;
    size_t tbegin, tend;
    treenode_t *left, *right;
    treenode_t() {}
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
        left->value = 0; left->to_flip = false;
    }
    void create_right()
    {
        right = alloc_node();
        right->tbegin = (tbegin+tend)/2+1; right->tend = tend;
        right->value = 0; right->to_flip = false;
    }
    uint32_t flipped_value(treenode_t* node)
        { return (node->tend - node->tbegin + 1) - value; }
    void pull()
    {
        if(to_flip)
        {
            value = flipped_value(this);
            if(tbegin < tend)
            {
                if(left == nullptr)
                    create_left();
                if(right == nullptr)
                    create_right();
                left ->to_flip = not left ->to_flip;
                right->to_flip = not right->to_flip;
            }
            to_flip = false;
        }
    }
    void flip_interval(uint32_t sbegin, uint32_t send)
    {
        pull();
        if(send < tbegin or tend < sbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_flip = not to_flip;
            pull();
        }
        else
        {
            pull();
            uint32_t t = 0;
            if(left == nullptr)
                create_left();
            left->flip_interval(sbegin, send);
            t += left->value;
            if(right == nullptr)
                create_right();
            right->flip_interval(sbegin, send);
            t += right->value;
            value = t;
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
    segment_tree(uint32_t abegin, uint32_t aend)
    {
        root.tbegin = abegin; root.tend = aend;
        root.value = 0; root.to_flip = false;
    }
    void flip_interval(uint32_t sbegin, uint32_t send)
        { root.flip_interval(sbegin, send); }
    uint32_t get(uint32_t sbegin, uint32_t send)
        { return root.get(sbegin, send); }
};

uint32_t clz(uint32_t x) { return __builtin_clz(x); }
uint32_t popcount(uint32_t x) { return __builtin_popcount(x); }
uint32_t log2floor(uint32_t x) { return 31 - clz(x); }

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, m;
    cin >> n >> m;
    static segment_tree tree(0, 1 << (log2floor(n+8) + 1));
    tree.flip_interval(tree.root.tbegin, tree.root.tend);
    for(uint32_t i = 0; i < m; i++)
    {
        char c; size_t a, b;
        cin >> c >> a >> b; a--; b--;
        if(c == '?')
            cout << tree.get(a, b) << "\n";
        else if(c == '*')
            tree.flip_interval(a, b);
    }
}
