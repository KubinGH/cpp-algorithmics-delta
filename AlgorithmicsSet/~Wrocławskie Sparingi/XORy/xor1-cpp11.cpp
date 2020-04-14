#include <bits/stdc++.h>

using namespace std;

template<typename T, size_t K>
struct int_trie
{
    struct node
    {
        node *p_child[2];
        size_t sum;
        node* child(size_t i)
        {
            if(not p_child[i])
                p_child[i] = new node {};
            return p_child[i];
        }
    } *root;

    int_trie() : root(new node {}) {}

    void insert(T x)
    {
        node* curr = root;
        curr->sum++;
        for(size_t i = K; i --> 0; )
            curr = curr->child(x >> i & 1), curr->sum++;
    }

    size_t order_of_key(T x, T xor_key = 0)
    {
        node* curr = root;
        size_t result = 0;
        for(size_t i = K; i --> 0; )
        {
            auto a = x >> i & 1, b = xor_key >> i & 1;
            if(a)
                result += curr->child(0 ^ b)->sum;
            curr = curr->child(a ^ b);
        }
        return result;
    }


    void destroy(node* curr)
    {
        for(auto i : {0, 1})
            if(curr->p_child[i])
                destroy(curr->p_child[i]);
        delete curr;
    }
    ~int_trie() { destroy(root); }
};

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n; uint64_t m;
    cin >> n >> m; m++;

    uint64_t result = 0;
    int_trie<uint64_t, 64> T;
    uint64_t x = 0;
    for(size_t j = 1; j <= n; j++)
    {
        T.insert(x);
        uint64_t a;
        cin >> a;
        x ^= a;
        result += T.order_of_key(m, x);
    }

    cout << result << endl;
}
