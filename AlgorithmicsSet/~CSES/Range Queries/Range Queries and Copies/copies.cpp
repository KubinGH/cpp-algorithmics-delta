#include <bits/stdc++.h>

using namespace std;

struct segment_tree_node
{
    int64_t value;
    shared_ptr<segment_tree_node> left, right;
};
using segment_tree = shared_ptr<segment_tree_node>;

segment_tree make_segment_tree(int64_t x)
{
    auto nd = make_shared<segment_tree_node>();
    nd->value = x; nd->left = nd->right = nullptr;
    return nd;
}
segment_tree make_segment_tree(segment_tree left, segment_tree right)
{
    auto nd = make_shared<segment_tree_node>();
    nd->value = left->value + right->value; nd->left = left; nd->right = right;
    return nd;
}

template<typename It>
segment_tree build_segment_tree(It first, It last)
{
    if(first+1 == last)
        return make_segment_tree(*first);
    auto mid = first + (last - first) / 2;
    return make_segment_tree(
        build_segment_tree(first, mid),
        build_segment_tree(mid, last)
    );
}

segment_tree setval(segment_tree tree, size_t l, size_t r, size_t p, int x)
{
    size_t m = (l+r)/2;
    if(l == r)
        return make_segment_tree(x);
    else if(p <= m)
        return make_segment_tree(setval(tree->left, l, m, p, x), tree->right);
    else
        return make_segment_tree(tree->left, setval(tree->right, m+1, r, p, x));
}
int64_t get(segment_tree tree, size_t l, size_t r, size_t a, size_t b)
{
    if(b < l or r < a)
        return 0;
    else if(a <= l and r <= b)
        return tree->value;
    else
        return get(tree->left, l, (l+r)/2, a, b) + get(tree->right, (l+r)/2+1, r, a, b);
}


int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int> A(n);
    for(auto& a : A)
        cin >> a;

    size_t w = 1 << __lg(2*n - 1);
    while(A.size() < w)
        A.push_back(0);

    vector<segment_tree> trees = {build_segment_tree(A.begin(), A.end())};

    while(q --> 0)
    {
        char t;
        cin >> t;

        if(t == '1')
        {
            size_t p, i; int x;
            cin >> p >> i >> x; p--; i--;
            trees[p] = setval(trees[p], 0, w - 1, i, x);
        }
        else if(t == '2')
        {
            size_t p, a, b;
            cin >> p >> a >> b; p--; a--; b--;
            cout << get(trees[p], 0, w - 1, a, b) << '\n';
        }
        else if(t == '3')
        {
            size_t p;
            cin >> p; p--;
            trees.push_back(trees[p]);
        }
    }
}
