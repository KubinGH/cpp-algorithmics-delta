#include <bits/stdc++.h>

using namespace std;

struct im_treap
{
    static mt19937 gen;
    using Tp = mt19937::result_type;

    struct node
    {
        Tp priority;
        node *left, *right;
        size_t size;
        pair<int, size_t> value, minim;
        bool invert;

        void update()
        {
            size = (left ? left->size : 0) + (right ? right->size : 0) + 1;
            minim = value;
            if( left) minim = min(minim,  left->minim);
            if(right) minim = min(minim, right->minim);
        }
        void push()
        {
            if(invert)
            {
                swap(left, right);
                if( left)  left->invert ^= 1;
                if(right) right->invert ^= 1;
                invert = false;
            }
        }
    } *root = nullptr;


    static node* meld(node* a, node* b)
    {
        if(not a or not b)
            return a ? a : b;
        a->push(); b->push();
        if(a->priority < b->priority)
        {
            b->left = meld(a, b->left); b->update();
            return b;
        }
        else
        {
            a->right = meld(a->right, b); a->update();
            return a;
        }
    }
    static pair<node*, node*> split(node* t, size_t key)
    {
        if(not t)
            return {nullptr, nullptr};
        t->push();
        auto c = (t->left ? t->left->size : 0) + 1;
        if(key < c)
        {
            auto [a, b] = split(t->left, key);
            t->left = b; t->update();
            return {a, t};
        }
        else
        {
            auto [a, b] = split(t->right, key - c);
            t->right = a; t->update();
            return {t, b};
        }
    }

    im_treap() {}

    template<typename It>
    im_treap(It first, It last)
    {
        root = build(first, last);
    }

    node* new_node(pair<int, size_t> value)
    {
        return new node { gen(), nullptr, nullptr, 1, value, value, false };
    }

    void dealloc(node* curr)
    {
        if(not curr) return;
        dealloc(curr->left);
        dealloc(curr->right);
        delete curr;
    }
    ~im_treap()
    {
        dealloc(root);
    }

    template<typename It>
    node* build(It first, It last)
    {
        if(first == last)
            return nullptr;
        else if(next(first) == last)
            return new_node(*first);
        else
            return meld(
                build(first, first + (last-first)/2),
                build(first + (last-first)/2, last)
            );
    }

    size_t min_value(node* curr)
    {
        curr->push();
        if(curr->minim == curr->value)
            return (curr->left ? curr->left->size : 0);
        else if(curr->left and curr->minim == curr->left->minim)
            return min_value(curr->left);
        else if(curr->right and curr->minim == curr->right->minim)
            return 1 + (curr->left ? curr->left->size : 0) + min_value(curr->right);
    }

    size_t min_value()
    {
        return min_value(root);
    }

    void pop_first(node*& curr)
    {
        curr->push();
        if(not curr->left)
        {
            auto c = curr;
            curr = curr->right;
            delete c;
        }
        else
        {
            pop_first(curr->left);
            curr->update();
        }
    }
    void pop_first()
    {
        return pop_first(root);
    }

    void reverse(size_t i)
    {
        if(i < 2) return;
        auto [C, R] = split(root, i);
        if(C) C->invert ^= 1;
        root = meld(C, R);
    }
};
mt19937 im_treap::gen;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n;
    while(cin >> n, n)
    {
        vector<pair<int, size_t>> A(n);
        for(size_t i = 0; i < n; i++)
            cin >> A[i].first, A[i].second = i;

        im_treap T(A.begin(), A.end());
        for(size_t i = 0; i < n; i++)
        {
            auto j = T.min_value();
            cout << i+j+1 << ' ';
            T.reverse(j + 1);
            T.pop_first();
        }
        cout << '\n';
    }
}
