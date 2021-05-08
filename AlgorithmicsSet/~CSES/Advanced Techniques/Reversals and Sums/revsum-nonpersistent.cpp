#include <bits/stdc++.h>

using namespace std;

mt19937_64 y_gen;

struct node
{
    node *left, *right;
    uint64_t priority;
    uint size;
    int value; int64_t sum;
    bool flip;

    void touch()
    {
        if(flip)
        {
            swap(left, right);
            if( left)  left->flip ^= 1;
            if(right) right->flip ^= 1;
            flip = false;
        }
    }

    void update()
    {
        sum = value + left->sum + right->sum;
        size = 1 + left->size + right->size;
    }
};

node ghost = {nullptr, nullptr, 0, 0, 0, 0, false};
node* ghost_ptr = &ghost;

size_t arena_size_sum(size_t k)
{
    return k ? (k > 1 ? 1u << k : 2) : 0;
}
size_t arena_size(size_t k)
{
    return arena_size_sum(k + 1) - arena_size_sum(k);
}
static size_t _node_cnt = 0;
node* new_node(int value = 0, node* left = ghost_ptr, node* right = ghost_ptr)
{
    _node_cnt++;
    static size_t i = 0;
    static vector<vector<node>> arenas;
    if(i >= arena_size_sum(arenas.size()))
        arenas.emplace_back(arena_size(arenas.size()));
    auto nd = &arenas.back()[i++ - arena_size_sum(arenas.size() - 1)];
    nd->left = left;
    nd->right = right;
    nd->priority = y_gen();
    nd->value = value;
    nd->flip = false;
    nd->update();
    return nd;
}

pair<node*, node*> split(node* root, size_t key)
{
    if(root == ghost_ptr)
        return {ghost_ptr, ghost_ptr};
    root->touch();
    if(key > root->left->size)
    {
        auto [l, r] = split(root->right, key - root->left->size - 1);
        root->right = l; root->update();
        return {root, r};
    }
    else
    {
        auto [l, r] = split(root->left, key);
        root->left = r; root->update();
        return {l, root};
    }
}

node* meld(node* first, node* second)
{
    if(first == ghost_ptr) return second;
    if(second == ghost_ptr) return first;
    first->touch(); second->touch();
    if(first->priority > second->priority)
    {
        first->right = meld(first->right, second); first->update();
        return first;
    }
    else
    {
        second->left = meld(first, second->left); second->update();
        return second;
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    vector<int> ini(n);
    for(auto& a : ini)
#ifndef STRESS
        cin >> a;
#else
        a = rand();
#endif

    function<node*(size_t, size_t)> build = [&](size_t l, size_t r) -> node* {
        if(l == r)
            return ghost_ptr;
        else if(l+1 == r)
            return new_node(ini[l]);
        else
            return meld(build(l, (l+r)/2), build((l+r)/2, r));
    };
    auto root = build(0, n);

    while(q --> 0)
    {
        char t; size_t a, b;
        #ifndef STRESS
        cin >> t >> a >> b; a--;
        #else
        t = '1' + rand()%2; a = (size_t)rand()%n; b = (size_t)rand()%n; if(a>b) swap(a, b); b++;
        #endif
        auto [left, mr] = split(root, a);
        auto [mid, right] = split(mr, b - a);
        if(t == '1')
            mid->flip = true;
        else if(t == '2')
            cout << mid->sum << '\n';
        root = meld(meld(left, mid), right);
    }
}
