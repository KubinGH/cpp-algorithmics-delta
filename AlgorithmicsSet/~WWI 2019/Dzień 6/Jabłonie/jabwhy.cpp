#include <bits/stdc++.h>

using namespace std;

struct binary_search_tree
{
    struct node
    {
        int value; size_t subtree = 1; int lazy = 0;
        node *left = nullptr, *right = nullptr;

        node(int _value) : value(_value) {}

        void touch()
        {
            if(left) left->lazy += lazy;
            if(right) right->lazy += lazy;
            value += lazy; lazy = 0;
        }

        void repair()
        {
            subtree = 1 + (left ? left->subtree : 0) + (right ? right->subtree : 0);
        }

        static node* merge(node* first, node* second)
        {
            if(first) first->touch();
            if(second) second->touch();
            if(first == nullptr) return second;
            if(second == nullptr) return first;
            if(rand() % 2)
                return merge(second, first);
            if(first->value > (second->left ? second->left->value : INT_MIN))
            {
                auto left2nd = second->left; second->left = nullptr;
                second->repair();
                first->left = merge(first->left, left2nd);
                first->right = merge(first->right, second->right);
            }
            else
                first->right = merge(first->right, second);
            first->repair();
            return first;
        }

        pair<node*, node*> split_lt(int point)
        {
            touch();
            if(left) left->touch();
            if(right) right->touch();
            if(value < point)
            {
                auto sleft = left, sright = right;
                left = right = nullptr;
                repair();
                auto sub = sright ? sright->split_lt(point) : make_pair(nullptr, nullptr);
                return {merge(this, merge(sleft, sub.first)), sub.second};
            }
            else if(left->value < point)
            {
                auto sleft = left, sright = right;
                left = right = nullptr;
                repair();
                return {sleft, merge(this, sright)};
            }
            else
                return {nullptr, this};
        }

        pair<node*, node*> split_k(size_t k)
        {
            if(k == 0)
                return {nullptr, this};
            touch();
            if(left) left->touch();
            if(right) right->touch();
            auto sleft = left, sright = right;
            left = nullptr; right = nullptr;
            repair();
            if(k <= (sleft ? sleft->subtree : 0))
                return {sleft, merge(this, sright)};
            else if(k <= (sleft ? sleft->subtree : 0) + 1)
                return {merge(this, sleft), sright};
            else
            {
                auto sub = sright->split_k(k - subtree - 1);
                return {merge(this, merge(sleft, sub.first)), sub.second};
            }
        }

        template<typename Callback>
        void inorder(Callback f)
        {
            touch();
            if(left) left->inorder(f);
            f(value);
            if(right) right->inorder(f);
        }
    } *root;

    template<typename Iterator>
    static node* near_perfect_bst(Iterator first, Iterator last)
    {
        if(first == last) return nullptr;
        auto mid = first + (last - first) / 2;
        node* root = new node(*mid);
        root->left = near_perfect_bst(first, mid);
        root->right = near_perfect_bst(mid+1, last);
        root->repair();
        return root;
    }

    binary_search_tree() : root(nullptr) {}

    binary_search_tree(vector<int> a)
    {
        sort(a.begin(), a.end());
        root = near_perfect_bst(a.begin(), a.end());
    }

    size_t size()
    {
        return root ? root->subtree : 0;
    }

    pair<binary_search_tree, binary_search_tree> split_k(size_t k)
    {
        auto p = root->split_k(k);
        auto t1 = p.first, t2 = p.second;
        pair<binary_search_tree, binary_search_tree> result;
        result.first.root = t1; result.second.root = t2;
        return result;
    }

    pair<binary_search_tree, binary_search_tree> split_lt(int value)
    {
        auto p = root->split_lt(value);
        auto lt = p.first, ge = p.second;
        pair<binary_search_tree, binary_search_tree> result;
        result.first.root = lt; result.second.root = ge;
        return result;
    }

    template<typename Callback>
    void inorder(Callback f)
    {
        if(root) root->inorder(f);
    }
};

binary_search_tree merge(binary_search_tree a, binary_search_tree b)
{
    a.root = binary_search_tree::node::merge(a.root, b.root);
    return a;
}
int main()
{
    size_t n, q;
    cin >> n >> q;

    vector<int> h(n);
    for(size_t i = 0; i < n; i++)
        cin >> h[i];

    binary_search_tree bst(h);

    auto pri = [](binary_search_tree& t) {
        cout << "{ ";
        t.inorder([](int x) { cout << x << " "; });
        cout << "}" << endl;
    };
    cout << "bst = ";
    pri(bst);

    while(q --> 0)
    {
        string cmd;
        cin >> cmd;
        if(cmd == "podlej")
        {
            size_t k;
            cin >> k;

            binary_search_tree first, second;
            tie(first, second) = bst.split_k(k);

            cout << "first = "; pri(first);
            cout << "second = "; pri(second);

            first.root->lazy++;
            bst = merge(first, second);
        }
        else if(cmd == "zbieraj")
        {
            int a, b;
            cin >> a >> b;

            binary_search_tree lt_a, le_b, gt_b;
            tie(lt_a, le_b) = bst.split_lt(a);
            cout << "lt_a = "; pri(lt_a);
            cout << "le_b = "; pri(le_b);
            cout << "gt_b = "; pri(gt_b);
            tie(le_b, gt_b) = le_b.split_lt(b + 1);

            cout << "lt_a = "; pri(lt_a);
            cout << "le_b = "; pri(le_b);
            cout << "gt_b = "; pri(gt_b);

            cout << le_b.size() << '\n';

            bst = merge(merge(lt_a, le_b), gt_b);
        }
        cout << "bst = ";
        pri(bst);
    }
}
