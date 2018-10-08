#include <bits/stdc++.h>

using namespace std;

template<typename T, typename MT>
struct segment_tree_node
{
    T value; MT mutate;
    segment_tree_node *left, *right;
};
template<typename T, typename ChildrenOp,
         typename MT, typename MutateOp, typename MergeOp>
struct dynamic_segment_tree
{
    using node = segment_tree_node<T, MT>;
    node root;
    ChildrenOp F;
    MutateOp M;
    MergeOp S;
    size_t w;
    dynamic_segment_tree(size_t n, ChildrenOp f = {}, MutateOp m = {}, MergeOp s = {})
    {
        w = 1 << (31 - __builtin_clz(2*n-1));
        F = move(f); M = move(m); S = move(s);
        root.value = ChildrenOp::identity; root.mutate = MutateOp::identity;
        root.left = nullptr; root.right = nullptr;
    }
    node* create_node()
    {
        node* y = new node;
        y->value = ChildrenOp::identity; y->mutate = MutateOp::identity;
        y->left = nullptr; y->right = nullptr;
        return y;
    }
    void pull(node* curr, size_t nodeL, size_t nodeR)
    {
        if(nodeL < nodeR)
        {
            if(curr->left == nullptr)
                curr->left = create_node();
            if(curr->right == nullptr)
                curr->right = create_node();
        }
        M(curr, nodeL, nodeR);
    }
    T get(node* curr, size_t nodeL, size_t nodeR, size_t getL, size_t getR)
    {
        pull(curr, nodeL, nodeR);
        if(nodeR < getL or getR < nodeL)
            return ChildrenOp::identity;
        else if(getL <= nodeL and nodeR <= getR)
            return curr->value;
        else
        {
            return F(get(curr->left, nodeL, (nodeL+nodeR)/2, getL, getR),
                     get(curr->right, (nodeL+nodeR)/2+1, nodeR, getL, getR));
        }
    }
    T get(size_t getL, size_t getR) { return get(&root, 0, w-1, getL, getR); }
    void mut(node* curr, size_t nodeL, size_t nodeR, size_t getL, size_t getR, MT value)
    {
        pull(curr, nodeL, nodeR);
        if(nodeR < getL or getR < nodeL)
            {}
        else if(getL <= nodeL and nodeR <= getR)
        {
            curr->mutate = S(curr->mutate, value);
            pull(curr, nodeL, nodeR);
        }
        else
        {
            mut(curr->left, nodeL, (nodeL+nodeR)/2, getL, getR, value);
            mut(curr->right, (nodeL+nodeR)/2+1, nodeR, getL, getR, value);
            curr->value = F(curr->left->value, curr->right->value);
        }
    }
    void mut(size_t getL, size_t getR, MT value) { return mut(&root, 0, w-1, getL, getR, value); }
};

struct add_u32
{
    static const uint32_t identity;
    uint32_t operator() (uint32_t a, uint32_t b) { return a+b; }
};
const uint32_t add_u32::identity = 0;

struct apply_inv
{
    static const bool identity;
    using node = segment_tree_node<uint32_t, bool>;
    void operator() (node* curr, size_t nodeL, size_t nodeR)
    {
        if(curr->mutate)
        {
            curr->value = (nodeR - nodeL + 1) - curr->value;
            if(nodeL < nodeR)
            {
                curr->left->mutate ^= 1;
                curr->right->mutate ^= 1;
            }
            curr->mutate = identity;
        }
    }
};
const bool apply_inv::identity = 0;

struct merge_inv
{
    bool operator() (bool a, bool b) { return a^b; }
};

typedef dynamic_segment_tree<
    uint32_t, add_u32,
    bool, apply_inv, merge_inv
> dynamic_inv_tree;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n, q;
    cin >> n >> q;
    dynamic_inv_tree tree(n);
    tree.mut(0, n-1, 1);
    while(q --> 0)
    {
        char c; uint32_t a, b;
        cin >> c >> a >> b; a--; b--;
        if(c == '?')
            cout << tree.get(a, b) << "\n";
        else if(c == '*')
            tree.mut(a, b, 1);
    }
}
