#include <bits/stdc++.h>

using namespace std;

const size_t MAX = 1e5, RANGE = 1 << 30, TH = 5000;

struct rect_t
{
    uint32_t x1, y1, x2, y2;
    rect_t() : x1(0), y1(0), x2(0), y2(0) {}
    rect_t(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) :
        x1(x1), y1(y1), x2(x2), y2(y2) {}
    bool is_degenerate() const
    {
        return x1 > x2 or y1 > y2;
    }
    rect_t intersect(const rect_t& o) const
    {
        return rect_t(max(x1, o.x1), max(y1, o.y1),
                      min(x2, o.x2), min(y2, o.y2));
    }
    uint32_t area()
    {
        if(is_degenerate()) return 0;
        else return (x2 - x1 + 1) * (y2 - y1 + 1);
    }
};


uint32_t k;
pair<rect_t, uint32_t> queries[MAX];


struct treenode_t
{
    uint32_t value, to_add;
    size_t tbegin, tend;
    treenode_t *left, *right;
    treenode_t() : left(nullptr), right(nullptr) {}
    treenode_t* alloc_node()
    {
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
        pull();
        if(send < tbegin or tend < sbegin)
            return 0;
        else if(sbegin <= tbegin and tend <= send)
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
    segment_tree(size_t abegin, size_t aend)
    {
        root.tbegin = abegin; root.tend = aend;
        root.value = 0; root.to_add = 0;
    }
    segment_tree() : segment_tree(0, RANGE) {}
    void add_interval(uint32_t sbegin, uint32_t send, uint32_t addvalue)
        { root.add_interval(sbegin, send, addvalue); }
    uint32_t get(uint32_t sbegin, uint32_t send)
        { return root.get(sbegin, send); }
};

struct tree2node_t
{
    segment_tree tree;
    uint32_t u, tbegin, tend;
    tree2node_t *left, *right;
    tree2node_t() : left(nullptr), right(nullptr) {}
    tree2node_t* alloc_node()
    {
        return new tree2node_t;
    }
    void create_left()
    {
        left = alloc_node();
        left->tbegin = tbegin; left->tend = (tbegin+tend)/2;
    }
    void create_right()
    {
        right = alloc_node();
        right->tbegin = (tbegin+tend)/2+1; right->tend = tend;
    }
    void pull()
    {
        for(uint32_t t = u; t < (k/TH)*TH; t++)
        {
            rect_t r = queries[t].first;
            uint32_t y1 = r.y1, y2 = r.y2, x1 = r.x1, x2 = r.x2, addvalue = queries[t].second;
            uint32_t cy1 = max(y1, tbegin), cy2 = min(y2, tend);
            if(cy1 > cy2)
                continue;
            tree.add_interval(x1, x2, (cy2 - cy1 + 1) * addvalue);
            if(left == nullptr)
                create_left();
            if(right == nullptr)
                create_right();
        }
        u = (k/TH)*TH;
    }
    uint32_t get(uint32_t y1, uint32_t y2, uint32_t x1, uint32_t x2)
    {
        pull();
        if(y2 < tbegin or tend < y1)
            return 0;
        else if(y1 <= tbegin and tend <= y2)
            return tree.get(x1, x2);
        else
        {
            if(left == nullptr)
                create_left();
            if(right == nullptr)
                create_right();
            return left->get(y1, y2, x1, x2) + right->get(y1, y2, x1, x2);
        }
    }
};

struct rect_tree
{
    tree2node_t root;
    rect_tree()
    {
        root.tbegin = 0; root.tend = RANGE;
    }
    uint32_t get(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2)
        { return root.get(y1, y2, x1, x2); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t q;
    cin >> q;
    rect_tree tree;
    for(uint32_t qi = 0; qi < q; qi++)
    {
        uint32_t p, a, b, c, d, v;
        cin >> p >> a >> b >> c >> d;
        rect_t r(a, c, b, d);
        if(p == 1)
        {
            cin >> v;
            queries[k++] = {r, v};
        }
        else if(p == 2)
        {
            uint32_t s = 0;
            for(uint32_t i = (k/TH)*TH; i < k; i++)
                s += r.intersect(queries[i].first).area() * queries[i].second;
            cout << s + tree.get(a, b, c, d) << "\n";
        }
    }
}
