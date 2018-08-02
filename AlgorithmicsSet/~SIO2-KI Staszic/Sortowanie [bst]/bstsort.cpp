#include <iostream>

using namespace std;

template<typename T>
struct binary_search_tree
{
    struct node
    {
        node *left, *right;
        T value;
        void clear_pointers() { left = nullptr; right = nullptr; }
        node() { clear_pointers(); }
        node(T v) : value(v) { clear_pointers(); }
    };
    node *root;
    binary_search_tree() { root = nullptr; }
    node* insert(T value)
    {
        if(root == nullptr)
        {
            root = new node(value);
            return root;
        }
        node *curr = root;
        bool done = false;
        while(not done)
        {
            if(value <= curr->value)
            {
                if(curr->left == nullptr)
                    curr->left = new node(value), done = true;
                curr = curr->left;
            }
            else
            {
                if(curr->right == nullptr)
                    curr->right = new node(value), done = true;
                curr = curr->right;
            }
        }
        return curr;
    }
    template<typename Callback>
    void traverse_inorder(Callback callback) const
    {
        traverse_inorder(callback, root);
    }
    template<typename Callback>
    void traverse_inorder(Callback callback, node* current) const
    {
        if(current == nullptr)
            return;
        traverse_inorder(callback, current->left);
        callback(current->value);
        traverse_inorder(callback, current->right);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    binary_search_tree<uint32_t> tree;
    for(uint32_t i = 0; i < n; i++)
    {
        uint32_t a;
        cin >> a;
        tree.insert(a);
    }
    tree.traverse_inorder([&](const uint32_t& a) { cout << a << " "; });
}