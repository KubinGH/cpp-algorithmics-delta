#include <bits/stdc++.h>

using namespace std;

mt19937 y_gen;

struct node
{
    node *left, *right;
    int size, value;
    int64_t sum;
    bool flip;

    size_t  left_size() const { return left ? left->size : 0; }
    size_t right_size() const { return right ? right->size : 0; }
    int64_t  left_sum() const { return left ? left->sum : 0; }
    int64_t right_sum() const { return right ? right->sum : 0; }

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
        sum = value + left_sum() + right_sum();
        size = 1 + left_size() + right_size();
    }
};

// need to tweak this amortized-constant allocator, otherwise
// overallocation happens (since up to twice the memory can be used with this
// method) - using persistence, there are 10 million allocations.
size_t arena_size_sum(size_t k)
{
    // return k ? (k > 1 ? 1u << k : 2) : 0;
    return k * (1 << 20);
}
size_t arena_size(size_t k)
{
    return arena_size_sum(k + 1) - arena_size_sum(k);
}
static size_t _node_cnt = 0;
node* new_node(int value = 0, node* left = nullptr, node* right = nullptr)
{
    _node_cnt++;
    static size_t i = 0;
    static vector<vector<node>> arenas;
    if(i >= arena_size_sum(arenas.size()))
        arenas.emplace_back(arena_size(arenas.size()));
    auto nd = &arenas.back()[i++ - arena_size_sum(arenas.size() - 1)];
    nd->left = left;
    nd->right = right;
    nd->value = value;
    nd->flip = false;
    nd->update();
    return nd;
}

pair<node*, node*> split(node* root, size_t key)
{
    if(not root)
        return {nullptr, nullptr};
    root->touch();
    if(key > root->left_size())
    {
        auto [l, r] = split(root->right, key - root->left_size() - 1);
        return {new_node(root->value, root->left, l), r};
    }
    else
    {
        auto [l, r] = split(root->left, key);
        return {l, new_node(root->value, r, root->right)};
    }
}

node* meld(node* first, node* second)
{
    if(not first) return second;
    if(not second) return first;
    first->touch(); second->touch();
    int i = uniform_int_distribution<int>{1, first->size + second->size}(y_gen);
    if(i < first->size)
        return new_node(first->value, first->left, meld(first->right, second));
    else
        return new_node(second->value, meld(first, second->left), second->right);
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, q;
    cin >> n >> q;

    node* root = nullptr;
    for(size_t i = 0; i < n; i++)
    {
        int value;
        #ifdef STRESS
        value = rand();
        #else
        cin >> value;
        #endif
        auto curr = new_node(value);
        root = meld(root, curr);
    }

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

    cerr << "cnt =  " << _node_cnt << endl;
}
