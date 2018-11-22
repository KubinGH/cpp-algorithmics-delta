#include <bits/stdc++.h>

using namespace std;

template<typename T, typename Compare = less<T>>
struct randomized_heap
{
    struct node
    {
        node *left, *right; T value;
    } *root = nullptr;
    Compare C;
    mt19937 gen; uint32_t bits_ready = 0; uint32_t bits;
    template<typename Iterator>
    randomized_heap(Iterator first, Iterator last, uint64_t seed = 42, Compare c = {})
    {
        gen.seed(seed);
        C = move(c);
        while(first != last)
            insert(*first++);
    }
    randomized_heap(uint64_t seed = 42, Compare c = {})
        : randomized_heap((T*)0, (T*)0, seed, c) {}
    bool next_bit()
    {
        if(not bits_ready)
            bits_ready = 32, bits = gen();
        bits_ready--; bool r = bits&1; bits >>= 1;
        return r;
    }
    node* merge(node* first, node* second)
    {
        if(not first or not second)
            return first ? first : second;
        if(C(second->value, first->value))
            swap(first, second);
        if(next_bit())
            swap(first->left, first->right);
        first->left = merge(first->left, second);
        return first;
    }
    void merge(randomized_heap& other) { root = merge(root, other.root); other.root = nullptr; }
    void insert(T x) { root = merge(root, new node {nullptr, nullptr, x}); }
    void pop() { node* pre = root; root = merge(pre->left, pre->right); delete pre; }
    const T& top() const { return root->value; };
    bool empty() const { return root == nullptr; };
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t m, n;
    cin >> m >> n;
    vector<pair<uint32_t, uint32_t>> V(n);
    for(uint32_t i = 0; i < n; i++)
        cin >> V[i].second >> V[i].first;
    sort(V.begin(), V.end());
    randomized_heap<uint32_t, greater<uint32_t>> H(time(0));
    uint32_t i = 0, r = 0;
    for(uint32_t h = 1; h <= m; h++)
    {
        while(i < n and V[i].first <= h)
            H.insert(V[i++].second);
        if(not H.empty())
            r += H.top(), H.pop();
    }
    cout << r;
}
