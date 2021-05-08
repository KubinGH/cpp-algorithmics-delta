#include <bits/stdc++.h>

using namespace std;

mt19937_64 y_gen;

struct node
{
    node *left, *right;
    uint64_t priority;
    uint size;
    char value;

    void touch() {}

    void update()
    {
        size = 1 + left->size + right->size;
    }
};

node nullnd_obj = {nullptr, nullptr, 0, 0, 0};
node* nullnd = &nullnd_obj;

size_t arena_size_sum(size_t k)
{
    return k ? (k > 1 ? 1u << k : 2) : 0;
}
size_t arena_size(size_t k)
{
    return arena_size_sum(k + 1) - arena_size_sum(k);
}
static size_t _node_cnt = 0;
node* new_node(char value = 0, node* left = nullnd, node* right = nullnd)
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
    nd->update();
    return nd;
}

pair<node*, node*> split(node* root, size_t key)
{
    if(root == nullnd)
        return {nullnd, nullnd};
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
    if(first == nullnd) return second;
    if(second == nullnd) return first;
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

    vector<char> ini(n);
    for(auto& a : ini)
        cin >> a;

    function<node*(size_t, size_t)> build = [&](size_t l, size_t r) -> node* {
        if(l == r)
            return nullnd;
        else if(l+1 == r)
            return new_node(ini[l]);
        else
            return meld(build(l, (l+r)/2), build((l+r)/2, r));
    };
    auto root = build(0, n);

    while(q --> 0)
    {
        size_t a, b;
        cin >> a >> b; a--;
        auto [left, mr] = split(root, a);
        auto [mid, right] = split(mr, b - a);
        root = meld(meld(left, right), mid);
    }

    function<void(node*)> dfs = [&](node* curr) {
        if(curr == nullnd)
            return;
        dfs(curr->left);
        cout << curr->value;
        dfs(curr->right);
    };
    dfs(root);
}
