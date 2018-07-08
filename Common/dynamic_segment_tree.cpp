#include <bits/stdc++.h>

using namespace std;

// these follow the same convention as the non-dynamic variants
// refer to the KTL source code

template<typename T, T(*F)(T, T), T NONE, typename I = uint32_t>
struct segment_tree_node
{
    I tbegin, tend;
    T value = NONE;
    segment_tree_node *left = nullptr, *right = nullptr;
    segment_tree_node() {}
    segment_tree_node(I i, I j) : tbegin(i), tend(j) {}
    void assert_children()
    {
        if(tbegin == tend)
            return;
        if(left == nullptr)
            left  = new segment_tree_node(tbegin, (tbegin+tend)/2);
        if(right == nullptr)
            right = new segment_tree_node((tbegin+tend)/2+1, tend);
    }
    T get(I sbegin, I send)
    {
        if(send < tbegin or tend < sbegin)
            return NONE;
        else if(sbegin <= tbegin and tend <= send)
            return value;
        else
            return F(left->get(sbegin, send), right->get(sbegin, send));
    }
};

template<typename T, T(*F)(T, T), T NONE, typename I = uint32_t>
struct dynamic_segment_tree
{
    using node = segment_tree_node<T, F, NONE, I>;
    node root;
    dynamic_segment_tree(I tbegin, I tend)
    {
        assert(__builtin_popcount(tend - tbegin + 1) == 1);
        root.tbegin = tbegin;
        root.tend = tend;
    }
    void set(I i, T value)
    {
        node* curr = &root;
        stack<node*> h;
        while(curr->tbegin < curr->tend)
        {
            h.push(curr);
            curr->assert_children();
            if(i <= curr->left->tend)
                curr = curr->left;
            else
                curr = curr->right;
        }
        curr->value = value;
        while(not h.empty())
        {
            h.top()->value = F(h.top()->left->value, h.top()->right->value);
            h.pop();
        }
    }
    T get(I sbegin, I send)
    {
        return root.get(sbegin, send);
    }
};

template<typename T, T(*F)(T, T), T NONE, T(*S)(T, T),
         T SET_NONE, typename I = uint32_t>
struct segment_tree_i_node
{
    using Pt = void(*)(segment_tree_i_node&);
    Pt P;
    I tbegin, tend;
    T value, to_set;
    segment_tree_i_node *left, *right;
    segment_tree_i_node() : segment_tree_i_node(0, 0, 0) {}
    segment_tree_i_node(Pt P) : segment_tree_i_node(P, 0, 0) {}
    segment_tree_i_node(Pt P, I i, I j)
        : P(P), tbegin(i), tend(j), value(NONE), to_set(SET_NONE),
          left(nullptr), right(nullptr) {}
    void assert_children()
    {
        if(tbegin == tend)
            return;
        if(left == nullptr)
            left  = new segment_tree_i_node(P, tbegin, (tbegin+tend)/2);
        if(right == nullptr)
            right = new segment_tree_i_node(P, (tbegin+tend)/2+1, tend);
    }
    void pull()
    {
        if(to_set != SET_NONE)
        {
            P(*this);
            to_set = SET_NONE;
        }
    }
    void set(I sbegin, I send, T value)
    {
        assert_children();
        if(send < tbegin or tend < sbegin)
            return;
        else if(sbegin <= tbegin and tend <= send)
        {
            to_set = S(to_set, value);
            pull();
        }
        else
        {
            pull();
            left ->set(sbegin, send, value);
            right->set(sbegin, send, value);
            this->value = F(left->value, right->value);
        }
    }
    T get(I sbegin, I send)
    {
        assert_children(); pull();
        if(send < tbegin or tend < sbegin)
            return NONE;
        else if(sbegin <= tbegin and tend <= send)
            return value;
        else
            return F(left->get(sbegin, send), right->get(sbegin, send));
    }
};


template<typename T, T(*F)(T, T), T NONE, T(*S)(T, T),
         T SET_NONE, typename I = uint32_t>
struct dynamic_segment_tree_i
{
    using node = segment_tree_i_node<T, F, NONE, S, SET_NONE, I>;
    node root;
    dynamic_segment_tree_i(void(*P)(node&), I tbegin, I tend)
    {
        assert(__builtin_popcount(tend - tbegin + 1) == 1);
        root.P = P;
        root.tbegin = tbegin;
        root.tend = tend;
    }
    void set(I sbegin, I send, T value) { return root.set(sbegin, send, value); }
    T get(I sbegin, I send) { return root.get(sbegin, send); }
};

uint32_t add_u32(uint32_t a, uint32_t b) { return a + b; }
template<typename node>
void pull_add(node& x)
{
    if(x.tbegin < x.tend)
    {
        x.left ->to_set += x.to_set;
        x.right->to_set += x.to_set;
    }
    x.value += (x.tend - x.tbegin + 1) * x.to_set;
}
int main()
{
    dynamic_segment_tree_i<uint32_t, add_u32, 0, add_u32, 0>
        tree(pull_add, 0u, (1u << 30) - 1u);
    tree.set(1, 4, 5);
    tree.set(2, 10, 10);
    tree.set(1<<29, (1<<29)+23, 42);
    cout << tree.get(0, (1 << 30) - 1);
}

