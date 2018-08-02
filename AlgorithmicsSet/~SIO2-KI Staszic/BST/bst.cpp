#include <iostream>

using namespace std;

template<typename T>
struct binary_search_tree
{
    struct node
    {
        node *left, *right, *parent; T value;
        void cp() { left = right = nullptr; }
        node() { cp(); parent = nullptr; }
        node(T v, node* p) : value(v), parent(p) { cp(); }
    };
    node* root = nullptr;
    node* insert_unique(T value)
    {
        if(root == nullptr)
            return (root = new node(value, nullptr));
        node* curr = root; bool done = false;
        while(not done)
        {
            if(value < curr->value)
            {
                if(curr->left == nullptr)
                    curr->left = new node(value, curr), done = true;
                curr = curr->left;
            }
            else if(value == curr->value)
                done = true;
            else
            {
                if(curr->right == nullptr)
                    curr->right = new node(value, curr), done = true;
                curr = curr->right;
            }
        }
        return curr;
    }
    node* find_min() const { return find_min(root); }
    node* find_min(node* from) const
    {
        node *curr = from;
        while(curr->left) curr = curr->left;
        return curr;
    }
    node* find(T value) const
    {
        node *curr = root; bool done = false;
        while(not done)
        {
            if(value < curr->value)
                curr = curr->left;
            else if(value > curr->value)
                curr = curr->right;
            else
                done = true;
        }
        return curr;
    }
    node* erase(node* it)
    {
        if(it == root)
        {
            if(it->left and not it->right)
            {
                it->left->parent = nullptr;
                root = it->left;
            }
            else if(not it->left and it->right)
            {
                it->right->parent = nullptr;
                root = it->right;
            }
            else if(not it->left and not it->right)
                root = nullptr;
            else if(it->left and it->right)
            {
                node* that = find_min(it->right);
                T v = that->value;
                erase(that);
                it->value = v;
                return it;
            }
            delete it;
            return root;
        }
        else if(not it->left and not it->right)
        {
            if(it->value <= it->parent->value)
                it->parent->left = nullptr;
            else
                it->parent->right = nullptr;
            delete it;
            return nullptr;
        }
        else if(it->left and not it->right)
        {
            if(it->value <= it->parent->value)
                it->parent->left  = it->left;
            else
                it->parent->right = it->left;
            it->left->parent = it->parent;
            delete it;
            return it->left;
        }
        else if(not it->left and it->right)
        {
            if(it->value <= it->parent->value)
                it->parent->left  = it->right;
            else
                it->parent->right = it->right;
            it->right->parent = it->parent;
            delete it;
            return it->right;
        }
        else if(it->left and it->right)
        {
            node* that = find_min(it->right);
            T v = that->value;
            erase(that);
            it->value = v;
            return it;
        }
    }
    node* erase(T value) { return erase(find(value)); }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    uint32_t n;
    cin >> n;
    binary_search_tree<uint32_t> tree;
    for(uint32_t i = 0; i < n; i++)
    {
        int32_t a; uint32_t b;
        cin >> a >> b;
        if(a == -1)
            tree.erase(b);
        else if(a == 0)
        {
            binary_search_tree<uint32_t>::node* it = tree.find(b);
            if(it->parent)
                cout << it->parent->value << "\n";
            else
                cout << "-1 \n";
        }
        else if(a == 1)
            tree.insert_unique(b);
    }
}